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
#include "design-line-xml.h"

#define MAX_SN 40

xmlDocPtr design_line_to_xml_doc(design_line_s *l)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(l);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_line_to_xml_node(l);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_line_to_xml_node(design_line_s *l)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;

  assert(l);

  n = xmlNewNode(NULL, BAD_CAST "line");
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

  return n;
}

xmlNodePtr design_line_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_line_s *design_line_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_line_root_node(doc);

  return design_line_from_xml_node(root);
}

design_line_s *design_line_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_line_s *l;

  assert(node);

  if (strcmp((char*)node->name, "line")) return NULL;

  l = design_line_create();
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
          else if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "end"))
            l->end = vertex_from_xml_node(node);
        }
      }
    }
  }

  return l;
}

design_line_s *design_line_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_line_s *l = NULL;
  vertex_s *vertex = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<line[^<]*>.*</line>"
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
        if (!strcmp((char *)root->name, "line"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            l = design_line_from_xml_doc(doc);
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
              if (!l) l = design_line_create();
              if (l->start) vertex_destroy(l->start);
              l->start = vertex;
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "end"))
            {
              if (!l) l = design_line_create();
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

