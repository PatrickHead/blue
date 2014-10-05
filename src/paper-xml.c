#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "paper-xml.h"

#define MAX_SN 40

xmlDocPtr paper_to_xml_doc(paper_s *p)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(p);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = paper_to_xml_node(p);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr paper_to_xml_node(paper_s *p)
{
  xmlNodePtr node = NULL;
  xmlNodePtr margins_node = NULL;
  xmlNodePtr color_node = NULL;
  char sn[MAX_SN];

  assert(p);

  node = xmlNewNode(NULL, BAD_CAST "paper");

  xmlNewChild(node, NULL, BAD_CAST "units", BAD_CAST units2str(p->units));
  
  xmlNewChild(node, NULL, BAD_CAST "size", BAD_CAST paper_size2str(p->size));
  
  xmlNewChild(node, NULL,
                    BAD_CAST "orientation",
                    BAD_CAST paper_orientation2str(p->orientation));
  
  margins_node = margins_to_xml_node(p->margins);
    xmlAddChild(node, xmlCopyNode(margins_node, 1));
  xmlFreeNode(margins_node);

  snprintf(sn, MAX_SN, "%f", p->width);
  xmlNewChild(node, NULL, BAD_CAST "width", BAD_CAST sn);
  
  snprintf(sn, MAX_SN, "%f", p->height);
  xmlNewChild(node, NULL, BAD_CAST "height", BAD_CAST sn);
  
  color_node = color_to_xml_node(p->color);
    xmlAddChild(node, xmlCopyNode(color_node, 1));
  xmlFreeNode(color_node);

  return node;
}

xmlNodePtr paper_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

paper_s *paper_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = paper_root_node(doc);

  return paper_from_xml_node(root);
}

paper_s *paper_from_xml_node(xmlNodePtr node)
{
  paper_s *p;
  xmlNodePtr value;

  assert(node);

  p = (paper_s *)malloc(sizeof(paper_s));
  memset(p, 0, sizeof(paper_s));

  if (strcmp((char*)node->name, "paper")) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "color"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "color"))
            p->color = color_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "units"))
          p->units = str2units((char*)value->content);
        else if (!strcmp((char*)node->name, "size"))
          p->size = str2paper_size((char*)value->content);
        else if (!strcmp((char*)node->name, "orientation"))
          p->orientation = str2paper_orientation((char*)value->content);
        else if (!strcmp((char*)node->name, "margins"))
          p->margins = margins_from_xml_node(node);
        else if (!strcmp((char*)node->name, "width"))
          p->width = strtod((char*)value->content, NULL);
        else if (!strcmp((char*)node->name, "height"))
          p->height = strtod((char*)value->content, NULL);
      }
    }
  }

  return p;
}

paper_s *paper_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  paper_s *p = NULL;
  margins_s *m = NULL;
  color_s *color = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<paper[^<]*>.*</paper>"
                    "|<color[^<]*/>"
                    "|<margins[^<]*>.*</margins>");
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
        if (!strcmp((char *)root->name, "paper"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            p = paper_from_xml_doc(doc);
            if (p) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "color"))
        {
          color = color_from_xml_doc(doc);
          if (color)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "color"))
            {
              if (!p) p = paper_create();
              if (p->color) color_destroy(p->color);
              p->color = color;
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "margins"))
        {
          if (!p) p = paper_create();
          if (p)
          {
            m = margins_from_xml_doc(doc);
            if (m)
            {
              paper_set_margins(p, m);
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

  return p;
}

