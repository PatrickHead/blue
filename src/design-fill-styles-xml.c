#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-fill-styles-xml.h"

#define MAX_SN 40

xmlDocPtr design_fill_styles_to_xml_doc(design_fill_styles_s *fss)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(fss);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_fill_styles_to_xml_node(fss);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_fill_styles_to_xml_node(design_fill_styles_s *fss)
{
  xmlNodePtr fssn;
  xmlNodePtr fsn;
  design_fill_style_s *fs;

  assert(fss);
  if (!fss->fill_styles) return NULL;

  fssn = xmlNewNode(NULL, BAD_CAST "fill-styles");
  if (!fssn) return NULL;

  for (fs = (design_fill_style_s *)list_head(fss->fill_styles);
       fs;
       fs = (design_fill_style_s *)list_next(fss->fill_styles))
  {
    fsn = design_fill_style_to_xml_node(fs);
    if (fsn)
    {
      xmlAddChild(fssn, xmlCopyNode(fsn, 1));
      xmlFreeNode(fsn);
    }
  }

  return fssn;
}

xmlNodePtr design_fill_styles_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_fill_styles_s *design_fill_styles_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_fill_styles_root_node(doc);

  return design_fill_styles_from_xml_node(root);
}

design_fill_styles_s *design_fill_styles_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_fill_styles_s *fss;
  design_fill_style_s *fs;

  assert(node);

  if (strcmp((char*)node->name, "fill-styles")) return NULL;

  fss = design_fill_styles_create();
  if (!fss) return NULL;
  if (!fss->fill_styles) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "fill-style"))
        {
          fs = design_fill_style_from_xml_node(node);
          list_insert(fss->fill_styles, fs, (void *)TAIL);
        }
      }
    }
  }

  return fss;
}

design_fill_styles_s *design_fill_styles_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_fill_styles_s *fss = NULL;
  design_fill_style_s *fs = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<fill-styles[^<]*>.*</fill-styles>"
                    "|<fill-style[^<]*>.*</fill-style>");
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
        if (!strcmp((char *)root->name, "fill-styles"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            fss = design_fill_styles_from_xml_doc(doc);
            if (fss) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "fill-style"))
        {
          if (!fss) fss = design_fill_styles_create();
          if (fss)
          {
            fs = design_fill_style_from_xml_doc(doc);
            if (fs)
            {
              design_fill_styles_add_fill_style(fss, fs);
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

  return fss;
}

