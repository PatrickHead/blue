#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-line-style-segments-xml.h"
#include "design-line-style-xml.h"

#define MAX_SN 40

xmlDocPtr design_line_style_to_xml_doc(design_line_style_s *ls)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(ls);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_line_style_to_xml_node(ls);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_line_style_to_xml_node(design_line_style_s *ls)
{
  xmlNodePtr n = NULL;
  xmlNodePtr dlssn = NULL;
  char sn[MAX_SN];

  assert(ls);

  n = xmlNewNode(NULL, BAD_CAST "line-style");
  if (!n) return NULL;

  if (ls->name)
  {
    snprintf(sn, MAX_SN, "%s", ls->name);
    xmlNewProp(n, BAD_CAST "name", BAD_CAST sn);
  }

  dlssn = design_line_style_segments_to_xml_node(ls->line_style_segments);
  if (dlssn)
  {
    xmlAddChild(n, xmlCopyNode(dlssn, 1));
    xmlFreeNode(dlssn);
  }

  return n;
}

xmlNodePtr design_line_style_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_line_style_s *design_line_style_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_line_style_root_node(doc);

  return design_line_style_from_xml_node(root);
}

design_line_style_s *design_line_style_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_line_style_s *ls;
  char *s;

  assert(node);

  if (strcmp((char*)node->name, "line-style")) return NULL;

  ls = design_line_style_create();
  if (!ls) return NULL;

  s = (char *)xmlGetProp(node, BAD_CAST "name");
  if (s)
    ls->name = strdup(s);

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "line-style-segments"))
          ls->line_style_segments =
            design_line_style_segments_from_xml_node(node);
      }
    }
  }

  return ls;
}

design_line_style_s *design_line_style_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_line_style_s *ls = NULL;
  design_line_style_segments_s *lss = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<line-style[^<]*>.*</line-style>"
                    "|<line-style-segments[^<]*>.*</line-style-segments>");
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
        if (!strcmp((char *)root->name, "line_style"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            ls = design_line_style_from_xml_doc(doc);
            if (ls) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "line-style-segments"))
        {
          lss = design_line_style_segments_from_xml_doc(doc);
          if (lss)
          {
            if (!ls) ls = design_line_style_create();
            if (ls)
            {
              design_line_style_set_line_style_segments(ls, lss);
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

  return ls;
}

