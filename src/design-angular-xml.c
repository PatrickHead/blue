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

#include "design-angular-xml.h"

#define MAX_SN 40

xmlDocPtr design_angular_to_xml_doc(design_angular_s *a)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(a);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_angular_to_xml_node(a);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_angular_to_xml_node(design_angular_s *a)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;
  char sn[MAX_SN];

  assert(a);

  n = xmlNewNode(NULL, BAD_CAST "angular");
  if (!n) return NULL;

  snprintf(sn, MAX_SN, "%f", a->angle);
  xmlNewChild(n, NULL, BAD_CAST "angle", BAD_CAST sn);

  vn = vertex_to_xml_node(a->alpha);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  vn = vertex_to_xml_node(a->beta);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  vn = vertex_to_xml_node(a->gamma);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  snprintf(sn, MAX_SN, "%f", a->gap);
  xmlNewChild(n, NULL, BAD_CAST "gap", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", a->extension);
  xmlNewChild(n, NULL, BAD_CAST "extension", BAD_CAST sn);

  return n;
}

xmlNodePtr design_angular_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_angular_s *design_angular_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_angular_root_node(doc);

  return design_angular_from_xml_node(root);
}

design_angular_s *design_angular_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_angular_s *a;

  assert(node);

  if (strcmp((char*)node->name, "angular")) return NULL;

  a = design_angular_create();
  if (!a) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "vertex"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "alpha"))
            a->alpha = vertex_from_xml_node(node);
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "beta"))
            a->beta = vertex_from_xml_node(node);
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "gamma"))
            a->gamma = vertex_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "angle"))
          a->angle = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "gap"))
          a->gap = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "extension"))
          a->extension = strtod((char *)value->content, NULL);
      }
    }
  }

  return a;
}

design_angular_s *design_angular_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_angular_s *a = NULL;
  vertex_s *vertex = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<angular[^<]*>.*</angular>"
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
        if (!strcmp((char *)root->name, "angular"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            a = design_angular_from_xml_doc(doc);
            if (a) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "vertex"))
        {
          vertex = vertex_from_xml_doc(doc);
          if (vertex)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "alpha"))
            {
              if (!a) a = design_angular_create();
              if (a->alpha) vertex_destroy(a->alpha);
              a->alpha = vertex;
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "beta"))
            {
              if (!a) a = design_angular_create();
              if (a->beta) vertex_destroy(a->beta);
              a->beta = vertex;
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "gamma"))
            {
              if (!a) a = design_angular_create();
              if (a->gamma) vertex_destroy(a->gamma);
              a->gamma = vertex;
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

  return a;
}
