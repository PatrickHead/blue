#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-elements-xml.h"

#define MAX_SN 40

xmlDocPtr design_elements_to_xml_doc(design_elements_s *es)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(es);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_elements_to_xml_node(es);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr design_elements_to_xml_node(design_elements_s *es)
{
  xmlNodePtr esn;
  xmlNodePtr en;
  design_element_s *e;

  assert(es);
  if (!es->elements) return NULL;

  esn = xmlNewNode(NULL, BAD_CAST "elements");
  if (!esn) return NULL;

  for (e = (design_element_s *)list_head(es->elements);
       e;
       e = (design_element_s *)list_next(es->elements))
  {
    en = design_element_to_xml_node(e);
    if (en)
    {
      xmlAddChild(esn, xmlCopyNode(en, 1));
      xmlFreeNode(en);
    }
  }

  return esn;
}

xmlNodePtr design_elements_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

design_elements_s *design_elements_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = design_elements_root_node(doc);

  return design_elements_from_xml_node(root);
}

design_elements_s *design_elements_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_elements_s *es;
  design_element_s *e;

  assert(node);

  if (strcmp((char*)node->name, "elements")) return NULL;

  es = design_elements_create();
  if (!es) return NULL;
  if (!es->elements) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "element"))
        {
          e = design_element_from_xml_node(node);
          list_insert(es->elements, e, (void *)TAIL);
        }
      }
    }
  }

  return es;
}

design_elements_s *design_elements_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_elements_s *es = NULL;
  design_element_s *e = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<elements[^<]*>.*</elements>"
                    "|<element[^<]*>.*</element>");
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
        if (!strcmp((char *)root->name, "elements"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            es = design_elements_from_xml_doc(doc);
            if (es) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "element"))
        {
          if (!es) es = design_elements_create();
          if (es)
          {
            e = design_element_from_xml_doc(doc);
            if (e)
            {
              design_elements_add_element(es, e);
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

  return es;
}

