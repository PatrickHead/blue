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
#include "design-dimension-xml.h"

#define MAX_SN 40

xmlDocPtr design_dimension_to_xml_doc(design_dimension_s *d)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(d);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_dimension_to_xml_node(d);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_dimension_to_xml_node(design_dimension_s *d)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;
  xmlNodePtr tn = NULL;
  char sn[MAX_SN];

  assert(d);

  n = xmlNewNode(NULL, BAD_CAST "dimension");
  if (!n) return NULL;

  xmlNewProp(n,
             BAD_CAST "type",
             BAD_CAST design_dimension_type2str(d->type));

  snprintf(sn, MAX_SN, "%f", d->text_size);
  xmlNewChild(n, NULL, BAD_CAST "text-size", BAD_CAST sn);

  vn = vertex_to_xml_node(d->text_location);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

  snprintf(sn, MAX_SN, "%d", d->precision);
  xmlNewChild(n, NULL, BAD_CAST "precision", BAD_CAST sn);

  switch (d->type)
  {
    case design_dimension_type_linear:
      tn = design_linear_to_xml_node(d->linear);
      break;
    case design_dimension_type_angular:
      tn = design_angular_to_xml_node(d->angular);
      break;
    case design_dimension_type_radial:
      tn = design_radial_to_xml_node(d->radial);
      break;
    default: break;
  }
  if (tn)
  {
    xmlAddChild(n, xmlCopyNode(tn, 1));
    xmlFreeNode(tn);
  }

  return n;
}

xmlNodePtr design_dimension_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_dimension_s *design_dimension_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_dimension_root_node(doc);

  return design_dimension_from_xml_node(root);
}

design_dimension_s *design_dimension_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_dimension_s *d;
  char *s;

  assert(node);

  d = design_dimension_create();
  if (!d) return NULL;

  if (strcmp((char*)node->name, "dimension")) return NULL;

  s = (char *)xmlGetProp(node, BAD_CAST "type");
  if (s)
    d->type = str2design_dimension_type(s);

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "vertex"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "text-location"))
            d->text_location = vertex_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char *)node->name, "text-size"))
          d->text_size = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "precision"))
          d->precision = atoi((char *)value->content);
        else if (!strcmp((char *)node->name, "angular"))
          d->angular = design_angular_from_xml_node(node);
        else if (!strcmp((char *)node->name, "linear"))
          d->linear = design_linear_from_xml_node(node);
        else if (!strcmp((char *)node->name, "radial"))
          d->radial = design_radial_from_xml_node(node);
      }
    }
  }

  return d;
}

design_dimension_s *design_dimension_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_dimension_s *d = NULL;
  design_angular_s *a = NULL;
  design_linear_s *l = NULL;
  design_radial_s *r = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<dimension[^<]*>.*</dimension>"
                    "|<angular[^<]*>.*</angular>"
                    "|<linear[^<]*>.*</linear>"
                    "|<radial[^<]*>.*</radial>"
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
        if (!strcmp((char *)root->name, "dimension"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            d = design_dimension_from_xml_doc(doc);
            if (d) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "angular"))
        {
          if (!d) d = design_dimension_create();
          if (d)
          {
            a = design_angular_from_xml_doc(doc);
            if (a)
            {
              design_dimension_set_angular(d, a);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "linear"))
        {
          if (!d) d = design_dimension_create();
          if (d)
          {
            l = design_linear_from_xml_doc(doc);
            if (l)
            {
              design_dimension_set_linear(d, l);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "radial"))
        {
          if (!d) d = design_dimension_create();
          if (d)
          {
            r = design_radial_from_xml_doc(doc);
            if (r)
            {
              design_dimension_set_radial(d, r);
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

  return d;
}

