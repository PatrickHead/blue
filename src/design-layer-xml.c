#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-layer-xml.h"

#define MAX_SN 40

xmlDocPtr design_layer_to_xml_doc(design_layer_s *l)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(l);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_layer_to_xml_node(l);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_layer_to_xml_node(design_layer_s *l)
{
  xmlNodePtr ln;
  xmlNodePtr defaults_node;
  xmlNodePtr elements_node;
  char sn[MAX_SN];

  assert(l);

  ln = xmlNewNode(NULL, BAD_CAST "layer");
  if (!ln) return NULL;
  
  snprintf(sn, MAX_SN, "%d", l->id);
  xmlNewProp(ln, BAD_CAST "id", BAD_CAST sn);

  if (l->name)
    xmlNewProp(ln, BAD_CAST "name", BAD_CAST l->name);

  xmlNewProp(ln,
             BAD_CAST "visibility",
             BAD_CAST design_visibility_type2str(l->visibility));

  if (l->defaults) defaults_node = design_defaults_to_xml_node(l->defaults);
  if (defaults_node)
  {
    xmlAddChild(ln, xmlCopyNode(defaults_node, 1));
    xmlFreeNode(defaults_node);
  }

  elements_node = design_elements_to_xml_node(l->elements);
  if (elements_node)
  {
    xmlAddChild(ln, xmlCopyNode(elements_node, 1));
    xmlFreeNode(elements_node);
  }

  return ln;
}

xmlNodePtr design_layer_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_layer_s *design_layer_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_layer_root_node(doc);

  return design_layer_from_xml_node(root);
}

design_layer_s *design_layer_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_layer_s *l;
  char *s;

  assert(node);

  if (strcmp((char*)node->name, "layer")) return NULL;

  l = design_layer_create();
  if (!l) return NULL;

  s = (char *)xmlGetProp(node, BAD_CAST "id");
  if (s)
    l->id = atoi(s);

  s = (char *)xmlGetProp(node, BAD_CAST "name");
  if (s)
    l->name = strdup(s);

  s = (char *)xmlGetProp(node, BAD_CAST "visibility");
  if (s)
    l->visibility = str2design_visibility_type(s);

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "defaults"))
        {
          if (l->defaults) design_defaults_destroy(l->defaults);
          l->defaults = design_defaults_from_xml_node(node);
        }
      }
      else if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "elements"))
        {
          if (l->elements) design_elements_destroy(l->elements);
          l->elements = design_elements_from_xml_node(node);
        }
      }
    }
  }

  return l;
}

design_layer_s *design_layer_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_layer_s *l = NULL;
  design_defaults_s *d = NULL;
  design_elements_s *es = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<layer[^<]*>.*</layer>"
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
        if (!strcmp((char *)root->name, "layer"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            l = design_layer_from_xml_doc(doc);
            if (l) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "defaults"))
        {
          if (!l) l = design_layer_create();
          if (l)
          {
            d = design_defaults_from_xml_doc(doc);
            if (d)
            {
              design_layer_set_defaults(l, d);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "elements"))
        {
          if (!l) l = design_layer_create();
          if (l)
          {
            es = design_elements_from_xml_doc(doc);
            if (es)
            {
              design_layer_set_elements(l, es);
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

  return l;
}

