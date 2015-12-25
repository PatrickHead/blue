/*!
    @file title-block-xml.c

    @brief SOURCE_BRIEF

    @timestamp Fri, 09 Oct 2015 05:38:21 +0000

    @author Patrick Head  mailto:patrickhead@gmail.com

    @copyright Copyright (C) 2014  Patrick Head

    @license
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.@n
    @n
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.@n
    @n
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

  /*!

    @file title-block-xml.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

  // Project related headers

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "title-block-xml.h"

#define MAX_SN 40

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlDocPtr title_block_to_xml_doc(title_block_s *tb)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

    // Sanity check parameters.
  assert(tb);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = title_block_to_xml_node(tb);

  xmlDocSetRootElement(doc, root);

    // Return RETVAL
  return doc;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlNodePtr title_block_to_xml_node(title_block_s *tb)
{
  xmlNodePtr node = NULL;
  xmlNodePtr color_node = NULL;
  char sn[MAX_SN];
  struct tm *tm;

    // Sanity check parameters.
  assert(tb);

  node = xmlNewNode(NULL, BAD_CAST "title-block");

  xmlNewChild(node, NULL, BAD_CAST "title", BAD_CAST tb->title);

  xmlNewChild(node, NULL, BAD_CAST "part", BAD_CAST tb->part);

  xmlNewChild(node, NULL, BAD_CAST "provider", BAD_CAST tb->provider);

  xmlNewChild(node, NULL, BAD_CAST "consumer", BAD_CAST tb->consumer);

  xmlNewChild(node, NULL, BAD_CAST "revision", BAD_CAST tb->revision);

  xmlNewChild(node, NULL, BAD_CAST "reference", BAD_CAST tb->reference);
  
  snprintf(sn, MAX_SN, "%d", tb->page);
  xmlNewChild(node, NULL, BAD_CAST "page", BAD_CAST sn);
  
  snprintf(sn, MAX_SN, "%d", tb->of);
  xmlNewChild(node, NULL, BAD_CAST "of", BAD_CAST sn);
  
  tm = gmtime(&(tb->time));
  strftime(sn, 40, "%Y-%m-%dT%H:%M:%SZ", tm);
  xmlNewChild(node, NULL, BAD_CAST "time", BAD_CAST sn);

  color_node = color_to_xml_node(tb->background_color);
    xmlAddChild(node, xmlCopyNode(color_node, 1));
  xmlFreeNode(color_node);

  color_node = color_to_xml_node(tb->line_color);
    xmlAddChild(node, xmlCopyNode(color_node, 1));
  xmlFreeNode(color_node);

  color_node = color_to_xml_node(tb->text_color);
    xmlAddChild(node, xmlCopyNode(color_node, 1));
  xmlFreeNode(color_node);

    // Return RETVAL
  return node;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlNodePtr title_block_root_node(xmlDocPtr doc)
{
    // Return RETVAL
  return xmlDocGetRootElement(doc);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

title_block_s *title_block_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

    // Sanity check parameters.
  assert(doc);

  root = title_block_root_node(doc);

    // Return RETVAL
  return title_block_from_xml_node(root);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

title_block_s *title_block_from_xml_node(xmlNodePtr node)
{
  title_block_s *tb;
  xmlNodePtr value;
  struct tm tm;

    // Sanity check parameters.
  assert(node);

  tb = (title_block_s *)malloc(sizeof(title_block_s));
  memset(tb, 0, sizeof(title_block_s)); 

  if (strcmp((char*)node->name, "title-block"))
      // Return RETVAL
  return NULL;

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
            tb->background_color = color_from_xml_node(node);
          else if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"),
                                              "line-color"))
            tb->line_color = color_from_xml_node(node);
          else if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"),
                                              "text-color"))
            tb->text_color = color_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "title"))
          strncpy(tb->title, (char*)value->content, 30);
        else if (!strcmp((char*)node->name, "part"))
          strncpy(tb->part, (char*)value->content, 30);
        else if (!strcmp((char*)node->name, "provider"))
          strncpy(tb->provider, (char*)value->content, 20);
        else if (!strcmp((char*)node->name, "consumer"))
          strncpy(tb->consumer, (char*)value->content, 20);
        else if (!strcmp((char*)node->name, "revision"))
          strncpy(tb->revision, (char*)value->content, 10);
        else if (!strcmp((char*)node->name, "reference"))
          strncpy(tb->reference, (char*)value->content, 10);
        else if (!strcmp((char*)node->name, "page"))
          tb->page = (int)strtol((char*)value->content, NULL, 0);
        else if (!strcmp((char*)node->name, "of"))
          tb->of = (int)strtol((char*)value->content, NULL, 0);
        else if (!strcmp((char*)node->name, "time"))
        {
          strptime((char*)value->content, "%Y-%m-%dT%H:%M:%SZ", &tm);
          tb->time = timegm(&tm);
        }
      }
    }
  }

    // Return RETVAL
  return tb;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

title_block_s *title_block_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  title_block_s *tb = NULL;
  color_s *color = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<title-block[^<]*>.*</title-block>"
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
        if (!strcmp((char *)root->name, "title-block"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            tb = title_block_from_xml_doc(doc);
            if (tb) doc_list_consume(dl, dl->keep[i]);
          }
          if (tb) title_block_destroy(tb);
        }
        else if (!strcmp((char *)root->name, "color"))
        {
          color = color_from_xml_doc(doc);
          if (color)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"),
                        "background-color"))
            {
              if (!tb) tb = title_block_create();
              if (tb->background_color) color_destroy(tb->background_color);
              tb->background_color = color;
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"),
                        "line-color"))
            {
              if (!tb) tb = title_block_create();
              if (tb->line_color) color_destroy(tb->line_color);
              tb->line_color = color;
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"),
                        "text-color"))
            {
              if (!tb) tb = title_block_create();
              if (tb->text_color) color_destroy(tb->text_color);
              tb->text_color = color;
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

    // Return RETVAL
  return tb;
}

