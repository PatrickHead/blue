#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-defaults-xml.h"
#include "design-tolerance-xml.h"

#define MAX_SN 40

xmlDocPtr design_tolerance_to_xml_doc(design_tolerance_s *t)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(t);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_tolerance_to_xml_node(t);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_tolerance_to_xml_node(design_tolerance_s *t)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;
  char sn[MAX_SN];

  assert(t);

  n = xmlNewNode(NULL, BAD_CAST "tolerance");
  if (!n) return NULL;

  vn = vertex_to_xml_node(t->location);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  snprintf(sn, MAX_SN, "%f", t->text_size);
  xmlNewChild(n, NULL, BAD_CAST "text-size", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", t->plus);
  xmlNewChild(n, NULL, BAD_CAST "plus", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", t->minus);
  xmlNewChild(n, NULL, BAD_CAST "minus", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%d", t->precision);
  xmlNewChild(n, NULL, BAD_CAST "precision", BAD_CAST sn);

  return n;
}

xmlNodePtr design_tolerance_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_tolerance_s *design_tolerance_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_tolerance_root_node(doc);

  return design_tolerance_from_xml_node(root);
}

design_tolerance_s *design_tolerance_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_tolerance_s *t;

  assert(node);

  if (strcmp((char*)node->name, "tolerance")) return NULL;

  t = design_tolerance_create();
  if (!t) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "vertex"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "location"))
            t->location = vertex_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char *)node->name, "text-size"))
          t->text_size = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "plus"))
          t->plus = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "minus"))
          t->minus = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "precision"))
          t->precision = atoi((char *)value->content);
      }
    }
  }

  return t;
}

design_tolerance_s *design_tolerance_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_tolerance_s *t = NULL;
  vertex_s *vertex = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<tolerance[^<]*>.*</tolerance>"
                    "|<vertex[^<]*/>"
                    "|<defaults[^<]*>.*</defaults>");
  if (!dl) return NULL;

    // Process any matching XML documents

  for (i = 0; i < dl->nkeep; i++)
  {
    doc = xmlReadMemory(dl->keep[i], strlen(dl->keep[i]), NULL, "UTF-8", 0);
    if (doc)
    {
      root = xmlDocGetRootElement(doc);
      if (root)
      {
        if (!strcmp((char *)root->name, "tolerance"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            t = design_tolerance_from_xml_doc(doc);
            if (t) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "vertex"))
        {
          vertex = vertex_from_xml_doc(doc);
          if (vertex)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "location"))
            {
              if (!t) t = design_tolerance_create();
              if (t->location) vertex_destroy(t->location);
              t->location = vertex;
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "defaults"))
        {
          defaults = design_defaults_from_xml_doc(doc);
          if (defaults)
          {
            design_defaults_push(defaults);
            doc_list_consume(dl, dl->keep[i]);
          }
        }
      }
      xmlFreeDoc(doc);
    }
  }

    // Emit all non-matching XML documents

  if (outfile)
  {
    for (i = 0; i < dl->nlist; i++)
    {
      if (!dl->list[i]) continue;
      doc = xmlReadMemory(dl->list[i], strlen(dl->list[i]), NULL, "UTF-8", 0);
      if (doc)
      {
        xmlDocFormatDumpEnc(outfile, doc, "UTF-8", 1);
        xmlFreeDoc(doc);
      }
    }
  }

  return t;
}

