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
#include "design-radial-xml.h"

#define MAX_SN 40

xmlDocPtr design_radial_to_xml_doc(design_radial_s *r)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(r);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_radial_to_xml_node(r);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_radial_to_xml_node(design_radial_s *r)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;
  char sn[MAX_SN];

  assert(r);

  n = xmlNewNode(NULL, BAD_CAST "radial");
  if (!n) return NULL;

  xmlNewProp(n, BAD_CAST "type", BAD_CAST design_radial_type2str(r->type));

  vn = vertex_to_xml_node(r->center);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  snprintf(sn, MAX_SN, "%f", r->major);
  xmlNewChild(n, NULL, BAD_CAST "major", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", r->minor);
  xmlNewChild(n, NULL, BAD_CAST "minor", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", r->angle);
  xmlNewChild(n, NULL, BAD_CAST "angle", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", r->leader);
  xmlNewChild(n, NULL, BAD_CAST "leader", BAD_CAST sn);

  return n;
}

xmlNodePtr design_radial_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_radial_s *design_radial_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_radial_root_node(doc);

  return design_radial_from_xml_node(root);
}

design_radial_s *design_radial_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_radial_s *r;
  char *s;

  assert(node);

  if (strcmp((char*)node->name, "radial")) return NULL;

  r = design_radial_create();
  if (!r) return NULL;

  s = (char *)xmlGetProp(node, BAD_CAST "type");
  if (s)
    r->type = str2design_radial_type(s);

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
            r->center = vertex_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "major"))
          r->major = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "minor"))
          r->minor = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "angle"))
          r->angle = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "leader"))
          r->leader = strtod((char *)value->content, NULL);
      }
    }
  }

  return r;
}

design_radial_s *design_radial_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_radial_s *r = NULL;
  vertex_s *vertex = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<radial[^<]*>.*</radial>"
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
        if (!strcmp((char *)root->name, "radial"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            r = design_radial_from_xml_doc(doc);
            if (r) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "vertex"))
        {
          vertex = vertex_from_xml_doc(doc);
          if (vertex)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "center"))
            {
              if (!r) r = design_radial_create();
              if (r->center) vertex_destroy(r->center);
              r->center = vertex;
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

  return r;
}

