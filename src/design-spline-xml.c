#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "vertices-xml.h"
#include "design-defaults-xml.h"
#include "design-spline-xml.h"

#define MAX_SN 40

xmlDocPtr design_spline_to_xml_doc(design_spline_s *s)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(s);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_spline_to_xml_node(s);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_spline_to_xml_node(design_spline_s *s)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;

  assert(s);

  n = xmlNewNode(NULL, BAD_CAST "spline");
  if (!n) return NULL;

  vn = vertices_to_xml_node(s->vertices);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  return n;
}

xmlNodePtr design_spline_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_spline_s *design_spline_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_spline_root_node(doc);

  return design_spline_from_xml_node(root);
}

design_spline_s *design_spline_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_spline_s *s;

  assert(node);

  if (strcmp((char*)node->name, "spline")) return NULL;

  s = design_spline_create();
  if (!s) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "vertices"))
          s->vertices = vertices_from_xml_node(node);
      }
    }
  }

  return s;
}

design_spline_s *design_spline_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_spline_s *s = NULL;
  vertices_s *vertices = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<spline[^<]*>.*</spline>"
                    "|<vertices[^<]*>.*</vertices>"
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
        if (!strcmp((char *)root->name, "spline"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            s = design_spline_from_xml_doc(doc);
            if (s) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "vertices"))
        {
          vertices = vertices_from_xml_doc(doc);
          if (vertices)
          {
            if (!s) s = design_spline_create();
            if (s)
            {
              design_spline_set_vertices(s, vertices);
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

  return s;
}

