#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-layers-xml.h"

#define MAX_SN 40

xmlDocPtr design_layers_to_xml_doc(design_layers_s *ls)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(ls);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_layers_to_xml_node(ls);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_layers_to_xml_node(design_layers_s *ls)
{
  xmlNodePtr lsn;
  xmlNodePtr ln;
  design_layer_s *l;

  assert(ls);

  lsn = xmlNewNode(NULL, BAD_CAST "layers");
  if (!lsn) return NULL;

  if (ls->layers)
  {
    for (l = (design_layer_s *)list_head(ls->layers);
         l;
         l = (design_layer_s *)list_next(ls->layers))
    {
      ln = design_layer_to_xml_node(l);
      if (ln)
      {
        xmlAddChild(lsn, xmlCopyNode(ln, 1));
        xmlFreeNode(ln);
      }
    }
  }

  return lsn;
}

xmlNodePtr design_layers_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_layers_s *design_layers_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_layers_root_node(doc);

  return design_layers_from_xml_node(root);
}

design_layers_s *design_layers_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_layers_s *ls;
  design_layer_s *l;

  assert(node);

  if (strcmp((char*)node->name, "layers")) return NULL;

  ls = design_layers_create();
  if (!ls) return NULL;
  if (!ls->layers) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "layer"))
        {
          l = design_layer_from_xml_node(node);
          list_insert(ls->layers, l, (void *)TAIL);
        }
      }
    }
  }

  return ls;
}

design_layers_s *design_layers_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_layers_s *ls = NULL;
  design_layer_s *l = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<layers[^<]*>.*</layers>"
                    "|<layer[^<]*>.*</layer>");
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
        if (!strcmp((char *)root->name, "layers"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            ls = design_layers_from_xml_doc(doc);
            if (ls) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "layer"))
        {
          if (!ls) ls = design_layers_create();
          if (ls)
          {
            l = design_layer_from_xml_doc(doc);
            if (l)
            {
              design_layers_add_layer(ls, l);
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

