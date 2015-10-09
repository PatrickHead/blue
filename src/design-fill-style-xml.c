/*!
    @file design-fill-style-xml.c

    @brief SOURCE_BRIEF

    @timestamp Tue, 11 Nov 2014 07:22:33 +0000

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

    @file design-fill-style-xml.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

  // Project related headers

#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-fill-style-xml.h"

#define MAX_SN 40

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlDocPtr design_fill_style_to_xml_doc(design_fill_style_s *fs)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

    // Sanity check parameters.
  assert(fs);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_fill_style_to_xml_node(fs);

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

xmlNodePtr design_fill_style_to_xml_node(design_fill_style_s *fs)
{
  xmlNodePtr n = NULL;
  xmlNodePtr cn = NULL;
  char sn[MAX_SN];

    // Sanity check parameters.
  assert(fs);

  n = xmlNewNode(NULL, BAD_CAST "fill-style");
  if (!n) return NULL;

  if (fs->name)
    xmlNewProp(n, BAD_CAST "name", BAD_CAST fs->name);

  xmlNewProp(n,
             BAD_CAST "type",
             BAD_CAST design_fill_style_type2str(fs->type));

  snprintf(sn, MAX_SN, "%f", fs->line_weight);
  xmlNewChild(n, NULL, BAD_CAST "line-weight", BAD_CAST sn);

  if (fs->line_style)
    xmlNewChild(n, NULL, BAD_CAST "line-style", BAD_CAST fs->line_style);

  cn = color_to_xml_node(fs->background_color);
  if (cn)
  {
    xmlAddChild(n, xmlCopyNode(cn, 1));
    xmlFreeNode(cn);
  }

  cn = color_to_xml_node(fs->pattern_color);
  if (cn)
  {
    xmlAddChild(n, xmlCopyNode(cn, 1));
    xmlFreeNode(cn);
  }

  snprintf(sn, MAX_SN, "%f", fs->angle1);
  xmlNewChild(n, NULL, BAD_CAST "angle1", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", fs->spacing1);
  xmlNewChild(n, NULL, BAD_CAST "spacing1", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", fs->angle2);
  xmlNewChild(n, NULL, BAD_CAST "angle2", BAD_CAST sn);

  snprintf(sn, MAX_SN, "%f", fs->spacing2);
  xmlNewChild(n, NULL, BAD_CAST "spacing2", BAD_CAST sn);

  if (fs->source)
    xmlNewChild(n, NULL, BAD_CAST "source", BAD_CAST fs->source);

    // Return RETVAL
  return n;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlNodePtr design_fill_style_root_node(xmlDocPtr doc)
{
    // Sanity check parameters.
  assert(doc);
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

design_fill_style_s *design_fill_style_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

    // Sanity check parameters.
  assert(doc);

  root = design_fill_style_root_node(doc);

    // Return RETVAL
  return design_fill_style_from_xml_node(root);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_style_s *design_fill_style_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_fill_style_s *fs;
  char *s;

    // Sanity check parameters.
  assert(node);

  if (strcmp((char*)node->name, "fill-style")) return NULL;

  fs = design_fill_style_create();
  if (!fs) return NULL;

  s = (char *)xmlGetProp(node, BAD_CAST "name");
  if (s)
    fs->name = strdup(s);

  s = (char *)xmlGetProp(node, BAD_CAST "type");
  if (s)
    fs->type = str2design_fill_style_type(s);

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
            fs->background_color = color_from_xml_node(node);
          else if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"),
                                               "pattern-color"))
            fs->pattern_color = color_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "line-weight"))
          fs->line_weight = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "line-style"))
          fs->line_style = strdup((char *)value->content);
        else if (!strcmp((char*)node->name, "angle1"))
          fs->angle1 = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "spacing1"))
          fs->spacing1 = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "angle2"))
          fs->angle2 = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "spacing2"))
          fs->spacing2 = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "source"))
          fs->source = strdup((char *)value->content);
      }
    }
  }

    // Return RETVAL
  return fs;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_style_s *design_fill_style_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_fill_style_s *fs = NULL;
  color_s *color = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<fill-style[^<]*>.*</fill-style>"
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
        if (!strcmp((char *)root->name, "fill-style"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            fs = design_fill_style_from_xml_doc(doc);
            if (fs) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "color"))
        {
          color = color_from_xml_doc(doc);
          if (color)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"),
                                                 "background-color"))
            {
              if (!fs) fs = design_fill_style_create();
              design_fill_style_set_background_color(fs, color);
              doc_list_consume(dl, dl->keep[i]);
            }
            else if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"),
                                                 "pattern-color"))
            {
              if (!fs) fs = design_fill_style_create();
              design_fill_style_set_pattern_color(fs, color);
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
  return fs;
}

