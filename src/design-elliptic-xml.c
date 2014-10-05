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
#include "design-elliptic-xml.h"

#define MAX_SN 40

xmlDocPtr design_elliptic_to_xml_doc(design_elliptic_s *e)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(e);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_elliptic_to_xml_node(e);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_elliptic_to_xml_node(design_elliptic_s *e)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;
  char sn[MAX_SN];

  assert(e);

  n = xmlNewNode(NULL, BAD_CAST "elliptic");
  if (!n) return NULL;

  vn = vertex_to_xml_node(e->center);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  snprintf(sn, MAX_SN, "%f", e->width);
  xmlNewChild(n, NULL, BAD_CAST "width", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", e->height);
  xmlNewChild(n, NULL, BAD_CAST "height", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", e->rotation);
  xmlNewChild(n, NULL, BAD_CAST "rotation", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", e->start_angle);
  xmlNewChild(n, NULL, BAD_CAST "start-angle", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", e->end_angle);
  xmlNewChild(n, NULL, BAD_CAST "end-angle", BAD_CAST sn);

  return n;
}

xmlNodePtr design_elliptic_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_elliptic_s *design_elliptic_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_elliptic_root_node(doc);

  return design_elliptic_from_xml_node(root);
}

design_elliptic_s *design_elliptic_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_elliptic_s *e;

  assert(node);

  if (strcmp((char*)node->name, "elliptic")) return NULL;

  e = design_elliptic_create();
  if (!e) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "vertex"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "center"))
            e->center = vertex_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "width"))
          e->width = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "height"))
          e->height = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "rotation"))
          e->rotation = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "start-angle"))
          e->start_angle = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "end-angle"))
          e->end_angle = strtod((char *)value->content, NULL);
      }
    }
  }

  return e;
}

design_elliptic_s *design_elliptic_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_elliptic_s *e = NULL;
  vertex_s *vertex;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<elliptic[^<]*>.*</elliptic>"
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
        if (!strcmp((char *)root->name, "elliptic"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            e = design_elliptic_from_xml_doc(doc);
            if (e) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "vertex"))
        {
          vertex = vertex_from_xml_doc(doc);
          if (vertex)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "center"))
            {
              if (!e) e = design_elliptic_create();
              if (e->center) vertex_destroy(e->center);
              e->center = vertex;
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

  return e;
}

