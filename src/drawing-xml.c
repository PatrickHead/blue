#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "paper-xml.h"
#include "border-xml.h"
#include "title-block-xml.h"
#include "design-xml.h"
#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "drawing-xml.h"

#define MAX_SN 40

xmlDocPtr drawing_to_xml_doc(drawing_s *d)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(d);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = drawing_to_xml_node(d);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr drawing_to_xml_node(drawing_s *d)
{
  xmlNodePtr node = NULL;
  xmlNodePtr subnode = NULL;

  assert(d);

  node = xmlNewNode(NULL, BAD_CAST "drawing");

  if (d->paper)
  {
    subnode = paper_to_xml_node(d->paper);
    xmlAddChild(node, xmlCopyNode(subnode, 1));
  }

  if (d->border)
  {
    subnode = border_to_xml_node(d->border);
    xmlAddChild(node, xmlCopyNode(subnode, 1));
  }

  if (d->title_block)
  {
    subnode = title_block_to_xml_node(d->title_block);
    xmlAddChild(node, xmlCopyNode(subnode, 1));
  }

  if (d->design)
  {
    subnode = design_to_xml_node(d->design);
    xmlAddChild(node, xmlCopyNode(subnode, 1));
  }

  return node;
}

xmlNodePtr drawing_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

drawing_s *drawing_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = drawing_root_node(doc);

  return drawing_from_xml_node(root);
}

drawing_s *drawing_from_xml_node(xmlNodePtr node)
{
  drawing_s *d;
  xmlNodePtr value;

  assert(node);

  d = drawing_create();

  if (strcmp((char*)node->name, "drawing"))
    return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value->type == XML_TEXT_NODE)
      {
        if (!strcmp((char*)node->name, "paper"))
          d->paper = paper_from_xml_node(node);
        else if (!strcmp((char*)node->name, "border"))
          d->border = border_from_xml_node(node);
        else if (!strcmp((char*)node->name, "title-block"))
          d->title_block = title_block_from_xml_node(node);
        else if (!strcmp((char*)node->name, "design"))
          d->design = design_from_xml_node(node);
      }
    }
  }

  return d;
}

drawing_s *drawing_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  drawing_s *d = NULL;
  paper_s *paper = NULL;
  border_s *border = NULL;
  title_block_s *title_block = NULL;
  design_s *design = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<drawing[^<]*>.*</drawing>"
                    "|<paper[^<]*>.*</paper>"
                    "|<border[^<]*>.*</border>"
                    "|<title-block[^<]*>.*</title-block>"
                    "|<design[^<]*>.*</design>");
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
        if (!strcmp((char *)root->name, "drawing"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            d = drawing_from_xml_doc(doc);
            if (d) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "paper"))
        {
          if (!d) d = drawing_create();
          if (d)
          {
            paper = paper_from_xml_doc(doc);
            if (paper)
            {
              drawing_set_paper(d, paper);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "border"))
        {
          if (!d) d = drawing_create();
          if (d)
          {
            border = border_from_xml_doc(doc);
            if (border)
            {
              drawing_set_border(d, border);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "title-block"))
        {
          if (!d) d = drawing_create();
          if (d)
          {
            title_block = title_block_from_xml_doc(doc);
            if (title_block)
            {
              drawing_set_title_block(d, title_block);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "design"))
        {
          if (!d) d = drawing_create();
          if (d)
          {
            design = design_from_xml_doc(doc);
            if (design)
            {
              drawing_set_design(d, design);
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

