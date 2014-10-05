#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "margins-xml.h"

#define MAX_SN 40

xmlDocPtr margins_to_xml_doc(margins_s *m)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

  assert(m);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = margins_to_xml_node(m);

  xmlDocSetRootElement(doc, root);

  return doc;
}

xmlNodePtr margins_to_xml_node(margins_s *m)
{
  xmlNodePtr node = NULL;
  char sn[MAX_SN];

  assert(m);

  node = xmlNewNode(NULL, BAD_CAST "margins");

  xmlNewChild(node, NULL, BAD_CAST "units", BAD_CAST units2str(m->units));
  
  snprintf(sn, MAX_SN, "%f", m->left);
  xmlNewChild(node, NULL, BAD_CAST "left", BAD_CAST sn);
  
  snprintf(sn, MAX_SN, "%f", m->right);
  xmlNewChild(node, NULL, BAD_CAST "right", BAD_CAST sn);
  
  snprintf(sn, MAX_SN, "%f", m->top);
  xmlNewChild(node, NULL, BAD_CAST "top", BAD_CAST sn);
  
  snprintf(sn, MAX_SN, "%f", m->bottom);
  xmlNewChild(node, NULL, BAD_CAST "bottom", BAD_CAST sn);
  
  return node;
}

xmlNodePtr margins_root_node(xmlDocPtr doc)
{
  assert(doc);
  return xmlDocGetRootElement(doc);
}

margins_s *margins_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

  assert(doc);

  root = margins_root_node(doc);

  return (margins_from_xml_node(root));
}

margins_s *margins_from_xml_node(xmlNodePtr node)
{
  margins_s *m;
  xmlNodePtr value;

  assert(node);

  m = (margins_s *)malloc(sizeof(margins_s));
  memset(m, 0, sizeof(margins_s));

  if (strcmp((char*)node->name, "margins")) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value->type == XML_TEXT_NODE)
      {
        if (!strcmp((char*)node->name, "units"))
          m->units = str2units((char*)value->content);
        else if (!strcmp((char*)node->name, "left"))
          m->left = strtod((char*)value->content, NULL);
        else if (!strcmp((char*)node->name, "right"))
          m->right = strtod((char*)value->content, NULL);
        else if (!strcmp((char*)node->name, "top"))
          m->top = strtod((char*)value->content, NULL);
        else if (!strcmp((char*)node->name, "bottom"))
          m->bottom = strtod((char*)value->content, NULL);
      }
    }
  }

  return m;
}

margins_s *margins_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  margins_s *m = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_new(infile,
                    "<?xml[^<]*?>",
                    "<margins[^<]*>.*</margins>");
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
        if (!strcmp((char *)root->name, "margins"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            m = margins_from_xml_doc(doc);
            if (m) doc_list_consume(dl, dl->keep[i]);
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

  return m;
}

