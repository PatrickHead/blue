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

#define MAX_SN 40

xmlDocPtr design_defaults_to_xml_doc(design_defaults_s *ds)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(ds);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_defaults_to_xml_node(ds);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_defaults_to_xml_node(design_defaults_s *ds)
{
  xmlNodePtr dsn;
  xmlNodePtr color_node;
  char sn[MAX_SN];

  assert(ds);

  dsn = xmlNewNode(NULL, BAD_CAST "defaults");
  if (!dsn) return NULL;

  xmlNewChild(dsn, NULL, BAD_CAST "units", BAD_CAST units2str(ds->units));

  snprintf(sn, MAX_SN, "%f", ds->line_weight);
  xmlNewChild(dsn, NULL, BAD_CAST "line-weight", BAD_CAST sn);

  xmlNewChild(dsn, NULL,
                    BAD_CAST "line-style",
                    ds->line_style ? BAD_CAST ds->line_style : BAD_CAST "NONE");

  xmlNewChild(dsn, NULL,
                    BAD_CAST "fill-style",
                    ds->fill_style ? BAD_CAST ds->fill_style : BAD_CAST "NONE");

  snprintf(sn, MAX_SN, "%f", ds->dimension_text_size);
  xmlNewChild(dsn, NULL, BAD_CAST "dimension-text-size", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%d", ds->dimension_precision);
  xmlNewChild(dsn, NULL, BAD_CAST "dimension-precision", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", ds->angular_gap);
  xmlNewChild(dsn, NULL, BAD_CAST "angular-gap", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", ds->angular_extension);
  xmlNewChild(dsn, NULL, BAD_CAST "angular-extension", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", ds->linear_gap);
  xmlNewChild(dsn, NULL, BAD_CAST "linear-gap", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", ds->linear_extension_above);
  xmlNewChild(dsn, NULL, BAD_CAST "linear-extension-above", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", ds->linear_extension_below);
  xmlNewChild(dsn, NULL, BAD_CAST "linear-extension-below", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", ds->tolerance_text_size);
  xmlNewChild(dsn, NULL, BAD_CAST "tolerance-text-size", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", ds->tolerance_plus);
  xmlNewChild(dsn, NULL, BAD_CAST "tolerance-plus", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", ds->tolerance_minus);
  xmlNewChild(dsn, NULL, BAD_CAST "tolerance-minus", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%d", ds->tolerance_precision);
  xmlNewChild(dsn, NULL, BAD_CAST "tolerance-precision", BAD_CAST sn);

  color_node = color_to_xml_node(ds->background_color);
    xmlAddChild(dsn, xmlCopyNode(color_node, 1));
  xmlFreeNode(color_node);

  color_node = color_to_xml_node(ds->element_color);
    xmlAddChild(dsn, xmlCopyNode(color_node, 1));
  xmlFreeNode(color_node);

  return dsn;
}

xmlNodePtr design_defaults_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_defaults_s *design_defaults_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_defaults_root_node(doc);

  return design_defaults_from_xml_node(root);
}

design_defaults_s *design_defaults_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_defaults_s *ds;

  assert(node);

  if (strcmp((char*)node->name, "defaults")) return NULL;

  ds = design_defaults_create();
  if (!ds) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "color"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"),
                                         "background-color"))
            ds->background_color = color_from_xml_node(node);
          else if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"),
                                              "element-color"))
            ds->element_color = color_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "units"))
          ds->units = str2units((char *)value->content);
        else if (!strcmp((char*)node->name, "line-weight"))
          ds->line_weight = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "line-style"))
          ds->line_style = strdup((char *)value->content);
        else if (!strcmp((char*)node->name, "fill-style"))
          ds->fill_style = strdup((char *)value->content);
        else if (!strcmp((char*)node->name, "dimension-text-size"))
          ds->dimension_text_size = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "dimension-precision"))
          ds->dimension_precision = strtol((char *)value->content, NULL, 10);
        else if (!strcmp((char *)node->name, "angular-gap"))
          ds->angular_gap = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "angular-extension"))
          ds->angular_extension = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "linear-gap"))
          ds->linear_gap = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "linear-extension-above"))
          ds->linear_extension_above = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "linear-extension-below"))
          ds->linear_extension_below = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "tolerance-text-size"))
          ds->tolerance_text_size = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "tolerance-plus"))
          ds->tolerance_plus = strtod((char *)value->content, NULL);
        else if (!strcmp((char *)node->name, "tolerance-minus"))
          ds->tolerance_minus = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "tolerance-precision"))
          ds->tolerance_precision = strtol((char *)value->content, NULL, 10);
      }
    }
  }

  return ds;
}

design_defaults_s *design_defaults_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_defaults_s *d = NULL;
  color_s *color = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<defaults[^<]*>.*</defaults>"
                    "|<color[^<]*/>");
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
        if (!strcmp((char *)root->name, "defaults"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            d = design_defaults_from_xml_doc(doc);
            if (d) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "color"))
        {
          color = color_from_xml_doc(doc);
          if (color)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"),
                                           "background-color"))
            {
              if (!d) d = design_defaults_create();
              if (d->background_color) color_destroy(d->background_color);
              d->background_color = color;
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"),
                                           "element-color"))
            {
              if (!d) d = design_defaults_create();
              if (d->element_color) color_destroy(d->element_color);
              d->element_color = color;
              doc_list_consume(dl, dl->keep[i]);
            }
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

