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
#include "design-polyline-xml.h"

#define MAX_SN 40

xmlDocPtr design_polyline_to_xml_doc(design_polyline_s *pl)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(pl);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_polyline_to_xml_node(pl);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_polyline_to_xml_node(design_polyline_s *pl)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;

  assert(pl);

  n = xmlNewNode(NULL, BAD_CAST "polyline");
  if (!n) return NULL;

  vn = vertices_to_xml_node(pl->vertices);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  return n;
}

xmlNodePtr design_polyline_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_polyline_s *design_polyline_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_polyline_root_node(doc);

  return design_polyline_from_xml_node(root);
}

design_polyline_s *design_polyline_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_polyline_s *pl;

  assert(node);

  if (strcmp((char*)node->name, "polyline")) return NULL;

  pl = design_polyline_create();
  if (!pl) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "vertices"))
          pl->vertices = vertices_from_xml_node(node);
      }
    }
  }

  return pl;
}

design_polyline_s *design_polyline_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_polyline_s *pl = NULL;
  vertices_s *vertices = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<polyline[^<]*>.*</polyline>"
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
        if (!strcmp((char *)root->name, "polyline"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            pl = design_polyline_from_xml_doc(doc);
            if (pl) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "vertices"))
        {
          vertices = vertices_from_xml_doc(doc);
          if (vertices)
          {
            if (!pl) pl = design_polyline_create();
            if (pl)
            {
              design_polyline_set_vertices(pl, vertices);
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

  return pl;
}

