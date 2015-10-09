/*!
    @file design-xml.c

    @brief SOURCE_BRIEF

    @timestamp Sun, 28 Dec 2014 01:58:54 +0000

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

    @file design-xml.c

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

#include "list.h"
#include "xml-extensions.h"
#include "doc-list.h"

#include "sieve.h"
#include "design-xml.h"

#define MAX_SN 40

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlDocPtr design_to_xml_doc(design_s *d)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

    // Sanity check parameters.
  assert(d);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_to_xml_node(d);

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

xmlNodePtr design_to_xml_node(design_s *d)
{
  xmlNodePtr node = NULL;
  xmlNodePtr defaults_node = NULL;
  xmlNodePtr line_styles_node = NULL;
  xmlNodePtr fill_styles_node = NULL;
  xmlNodePtr layers_node = NULL;
  char sn[MAX_SN];

    // Sanity check parameters.
  assert(d);

  node = xmlNewNode(NULL, BAD_CAST "design");

  if (d->defaults) defaults_node = design_defaults_to_xml_node(d->defaults);
  if (defaults_node)
  {
    xmlAddChild(node, xmlCopyNode(defaults_node, 1));
    xmlFreeNode(defaults_node);
  }

  if (d->line_styles)
    line_styles_node = design_line_styles_to_xml_node(d->line_styles);
  if (line_styles_node)
  {
    xmlAddChild(node, xmlCopyNode(line_styles_node, 1));
    xmlFreeNode(line_styles_node);
  }

  if (d->fill_styles)
    fill_styles_node = design_fill_styles_to_xml_node(d->fill_styles);
  if (fill_styles_node)
  {
    xmlAddChild(node, xmlCopyNode(fill_styles_node, 1));
    xmlFreeNode(fill_styles_node);
  }

  if (d->layers) layers_node = design_layers_to_xml_node(d->layers);
  if (layers_node)
  {
    xmlAddChild(node, xmlCopyNode(layers_node, 1));
    xmlFreeNode(layers_node);
  }

  snprintf(sn, MAX_SN, "%f", d->scaling_factor);
  xmlNewChild(node, NULL, BAD_CAST "scaling-factor", BAD_CAST sn);

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

xmlNodePtr design_root_node(xmlDocPtr doc)
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

design_s *design_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

    // Sanity check parameters.
  assert(doc);

  root = design_root_node(doc);

    // Return RETVAL
  return design_from_xml_node(root);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_s *design_from_xml_node(xmlNodePtr node)
{
  design_s *d;
  xmlNodePtr value;

    // Sanity check parameters.
  assert(node);

  d = design_create();

  if (strcmp((char*)node->name, "design")) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "defaults"))
        {
          if (d->defaults) design_defaults_destroy(d->defaults);
          d->defaults = design_defaults_from_xml_node(node);
        }
        if (!strcmp((char*)node->name, "line-styles"))
        {
          if (d->line_styles) design_line_styles_destroy(d->line_styles);
          d->line_styles = design_line_styles_from_xml_node(node);
        }
        if (!strcmp((char*)node->name, "fill-styles"))
        {
          if (d->fill_styles) design_fill_styles_destroy(d->fill_styles);
          d->fill_styles = design_fill_styles_from_xml_node(node);
        }
        else if (!strcmp((char*)node->name, "layers"))
        {
          if (d->layers) design_layers_destroy(d->layers);
          d->layers = design_layers_from_xml_node(node);
        }
        else if (!strcmp((char*)node->name, "scaling-factor"))
          d->scaling_factor = strtod((char *)value->content, NULL);
      }
    }
  }

    // Return RETVAL
  return d;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_s *design_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_s *d = NULL;
  design_defaults_s *defaults;
  design_line_styles_s *line_styles;
  design_fill_styles_s *fill_styles;
  design_layers_s *layers;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<design[^<]*>.*</design>"
                    "|<defaults[^<]*>.*</defaults>"
                    "|<line-styles[^<]*>.*</line-styles>"
                    "|<fill-styles[^<]*>.*</fill-styles>"
                    "|<layers[^<]*>.*</layers>");
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
        if (!strcmp((char *)root->name, "design"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            d = design_from_xml_doc(doc);
            if (d) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "defaults"))
        {
          if (!d) d = design_create();
          if (d)
          {
            defaults = design_defaults_from_xml_doc(doc);
            if (defaults)
            {
              design_set_defaults(d, defaults);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "line-styles"))
        {
          if (!d) d = design_create();
          if (d)
          {
            line_styles = design_line_styles_from_xml_doc(doc);
            if (line_styles)
            {
              design_set_line_styles(d, line_styles);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "fill-styles"))
        {
          if (!d) d = design_create();
          if (d)
          {
            fill_styles = design_fill_styles_from_xml_doc(doc);
            if (fill_styles)
            {
              design_set_fill_styles(d, fill_styles);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "layers"))
        {
          if (!d) d = design_create();
          if (d)
          {
            layers = design_layers_from_xml_doc(doc);
            if (layers)
            {
              design_set_layers(d, layers);
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
  return d;
}

