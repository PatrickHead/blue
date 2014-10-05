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
#include "design-linear-xml.h"

#define MAX_SN 40

xmlDocPtr design_linear_to_xml_doc(design_linear_s *l)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(l);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_linear_to_xml_node(l);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_linear_to_xml_node(design_linear_s *l)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;
  char sn[MAX_SN];

  assert(l);

  n = xmlNewNode(NULL, BAD_CAST "linear");
  if (!n) return NULL;


  vn = vertex_to_xml_node(l->start);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  vn = vertex_to_xml_node(l->end);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  snprintf(sn, MAX_SN, "%f", l->gap);
  xmlNewChild(n, NULL, BAD_CAST "gap", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", l->extension_above);
  xmlNewChild(n, NULL, BAD_CAST "extension-above", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", l->extension_below);
  xmlNewChild(n, NULL, BAD_CAST "extension-below", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", l->dimension);
  xmlNewChild(n, NULL, BAD_CAST "dimension", BAD_CAST sn);

  return n;
}

xmlNodePtr design_linear_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_linear_s *design_linear_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_linear_root_node(doc);

  return design_linear_from_xml_node(root);
}

design_linear_s *design_linear_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_linear_s *l;

  assert(node);

  if (strcmp((char*)node->name, "linear")) return NULL;

  l = design_linear_create();
  if (!l) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "vertex"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "start"))
            l->start = vertex_from_xml_node(node);
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "end"))
            l->end = vertex_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "gap"))
          l->gap = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "extension-above"))
          l->extension_above = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "extension-below"))
          l->extension_below = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "dimension"))
          l->dimension = strtod((char *)value->content, NULL);
      }
    }
  }

  return l;
}

design_linear_s *design_linear_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_linear_s *l = NULL;
  vertex_s *vertex = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<linear[^<]*>.*</linear>"
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
        if (!strcmp((char *)root->name, "linear"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            l = design_linear_from_xml_doc(doc);
            if (l) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "vertex"))
        {
          vertex = vertex_from_xml_doc(doc);
          if (vertex)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "start"))
            {
              if (!l) l = design_linear_create();
              if (l->start) vertex_destroy(l->start);
              l->start = vertex;
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "end"))
            {
              if (!l) l = design_linear_create();
              if (l->end) vertex_destroy(l->end);
              l->end = vertex;
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

  return l;
}

