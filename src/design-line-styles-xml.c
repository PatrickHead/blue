#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-line-styles-xml.h"

#define MAX_SN 40

xmlDocPtr design_line_styles_to_xml_doc(design_line_styles_s *lss)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(lss);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_line_styles_to_xml_node(lss);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_line_styles_to_xml_node(design_line_styles_s *lss)
{
  xmlNodePtr lssn;
  xmlNodePtr lsn;
  design_line_style_s *ls;

  assert(lss);
  if (!lss->line_styles) return NULL;

  lssn = xmlNewNode(NULL, BAD_CAST "line-styles");
  if (!lssn) return NULL;

  for (ls = (design_line_style_s *)list_head(lss->line_styles);
       ls;
       ls = (design_line_style_s *)list_next(lss->line_styles))
  {
    lsn = design_line_style_to_xml_node(ls);
    if (lsn)
    {
      xmlAddChild(lssn, xmlCopyNode(lsn, 1));
      xmlFreeNode(lsn);
    }
  }

  return lssn;
}

xmlNodePtr design_line_styles_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_line_styles_s *design_line_styles_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_line_styles_root_node(doc);

  return design_line_styles_from_xml_node(root);
}

design_line_styles_s *design_line_styles_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_line_styles_s *lss;
  design_line_style_s *ls;

  assert(node);

  if (strcmp((char*)node->name, "line-styles")) return NULL;

  lss = design_line_styles_create();
  if (!lss) return NULL;
  if (!lss->line_styles) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "line-style"))
        {
          ls = design_line_style_from_xml_node(node);
          list_insert(lss->line_styles, ls, (void *)TAIL);
        }
      }
    }
  }

  return lss;
}

design_line_styles_s *design_line_styles_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_line_styles_s *lss = NULL;
  design_line_style_s *ls = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<line-styles[^<]*>.*</line-styles>"
                    "|<line-style[^<]*>.*</line-style>");
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
        if (!strcmp((char *)root->name, "line-styles"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            lss = design_line_styles_from_xml_doc(doc);
            if (lss) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "line-style"))
        {
          if (!lss) lss = design_line_styles_create();
          if (lss)
          {
            ls = design_line_style_from_xml_doc(doc);
            if (ls)
            {
              design_line_styles_add_line_style(lss, ls);
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

  return lss;
}

