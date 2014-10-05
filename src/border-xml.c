#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "border-xml.h"

#define MAX_SN 40

xmlDocPtr border_to_xml_doc(border_s *b)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(b);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = border_to_xml_node(b);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr border_to_xml_node(border_s *b)
{
  xmlNodePtr node = NULL;
  xmlNodePtr margins_node = NULL;
  xmlNodePtr color_node = NULL;
  char sn[MAX_SN];

  assert(b);

  node = xmlNewNode(NULL, BAD_CAST "border");

  xmlNewChild(node, NULL, BAD_CAST "units", BAD_CAST units2str(b->units));
  
  snprintf(sn, MAX_SN, "%f", b->line_width);
  xmlNewChild(node, NULL, BAD_CAST "line-width", BAD_CAST sn);

  margins_node = margins_to_xml_node(b->margins);
    xmlAddChild(node, xmlCopyNode(margins_node, 1));
  xmlFreeNode(margins_node);

  color_node = color_to_xml_node(b->background_color);
    xmlAddChild(node, xmlCopyNode(color_node, 1));
  xmlFreeNode(color_node);

  color_node = color_to_xml_node(b->line_color);
    xmlAddChild(node, xmlCopyNode(color_node, 1));
  xmlFreeNode(color_node);

  return node;
}

xmlNodePtr border_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

border_s *border_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = border_root_node(doc);

  return border_from_xml_node(root);
}

border_s *border_from_xml_node(xmlNodePtr node)
{
  border_s *b;
  xmlNodePtr value;

  assert(node);

  b = (border_s *)malloc(sizeof(border_s));
  memset(b, 0, sizeof(border_s));

  if (strcmp((char*)node->name, "border")) return NULL;

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
            b->background_color = color_from_xml_node(node);
          else if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"),
                                              "line-color"))
            b->line_color = color_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "units"))
          b->units = str2units((char*)value->content);
        else if (!strcmp((char*)node->name, "line-width"))
          b->line_width = strtod((char*)value->content, NULL);
        else if (!strcmp((char*)node->name, "margins"))
          b->margins = margins_from_xml_node(node);
      }
    }
  }

  return b;
}

border_s *border_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  border_s *b = NULL;
  margins_s *m = NULL;
  color_s *color = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<border[^<]*>.*</border>"
                    "|<margins[^<]*>.*</margins>"
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
        if (!strcmp((char *)root->name, "border"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            b = border_from_xml_doc(doc);
            if (b) doc_list_consume(dl, dl->keep[i]);
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
              if (!b) b = border_create();
              if (b->background_color) color_destroy(b->background_color);
              b->background_color = color;
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"),
                        "line-color"))
            {
              if (!b) b = border_create();
              if (b->line_color) color_destroy(b->line_color);
              b->line_color = color;
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "margins"))
        {
          if (!b) b = border_create();
          if (b)
          {
            m = margins_from_xml_doc(doc);
            if (m)
            {
              border_set_margins(b, m);
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

  return b;
}

