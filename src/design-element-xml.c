/*!
    @file design-element-xml.c

    @brief SOURCE_BRIEF

    @timestamp Mon, 06 Jan 2014 15:17:36 +0000

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

    @file design-element-xml.c

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
#include "design-defaults-xml.h"
#include "design-element-xml.h"

#define MAX_SN 40

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlDocPtr design_element_to_xml_doc(design_element_s *e)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

    // Sanity check parameters.
  assert(e);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_element_to_xml_node(e);

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

xmlNodePtr design_element_to_xml_node(design_element_s *e)
{
  xmlNodePtr en;
  xmlNodePtr cn;
  xmlNodePtr tn;
  char sn[MAX_SN];

    // Sanity check parameters.
  assert(e);

  en = xmlNewNode(NULL, BAD_CAST "element");
  if (!en) return NULL;
  
  snprintf(sn, MAX_SN, "%d", e->id);
  xmlNewProp(en, BAD_CAST "id", BAD_CAST sn);

  xmlNewProp(en,
             BAD_CAST "type",
             BAD_CAST design_element_type2str(e->type));

  xmlNewChild(en, NULL, BAD_CAST "units", BAD_CAST units2str(e->units));

  snprintf(sn, MAX_SN, "%f", e->line_weight);
  xmlNewChild(en, NULL, BAD_CAST "line-weight", BAD_CAST sn);

  xmlNewChild(en,
              NULL,
              BAD_CAST "line-style",
              e->line_style ? BAD_CAST e->line_style : BAD_CAST "NONE");

  xmlNewChild(en,
              NULL,
              BAD_CAST "fill-style",
              e->fill_style ? BAD_CAST e->fill_style : BAD_CAST "NONE");

  cn = color_to_xml_node(e->color);
  if (cn)
  {
    xmlAddChild(en, xmlCopyNode(cn, 1));
    xmlFreeNode(cn);
  }

  tn = NULL;
  switch (e->type)
  {
    case design_element_type_dimension:
      tn = design_dimension_to_xml_node(e->dimension);
      break;
    case design_element_type_elliptic:
      tn = design_elliptic_to_xml_node(e->elliptic);
      break;
    case design_element_type_line:
      tn = design_line_to_xml_node(e->line);
      break;
    case design_element_type_point:
      tn = design_point_to_xml_node(e->point);
      break;
    case design_element_type_polyline:
      tn = design_polyline_to_xml_node(e->polyline);
      break;
    case design_element_type_spline:
      tn = design_spline_to_xml_node(e->spline);
      break;
    case design_element_type_text:
      tn = design_text_to_xml_node(e->text);
      break;
    case design_element_type_tolerance:
      tn = design_tolerance_to_xml_node(e->tolerance);
      break;
    case design_element_type_END: break;
  }
  if (tn)
  {
    xmlAddChild(en, xmlCopyNode(tn, 1));
    xmlFree(tn);
  }

    // Return RETVAL
  return en;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlNodePtr design_element_root_node(xmlDocPtr doc)
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

design_element_s *design_element_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

    // Sanity check parameters.
  assert(doc);

  root = design_element_root_node(doc);

    // Return RETVAL
  return design_element_from_xml_node(root);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_element_s *design_element_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_element_s *e;
  char *s;

    // Sanity check parameters.
  assert(node);

  if (strcmp((char*)node->name, "element")) return NULL;

  e = design_element_create();
  if (!e) return NULL;

  s = (char *)xmlGetProp(node, BAD_CAST "id");
  if (s)
    e->id = atoi(s);

  s = (char *)xmlGetProp(node, BAD_CAST "type");
  if (s)
    e->type = str2design_element_type(s);

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "color"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "color"))
            e->color = color_from_xml_node(node);
        }
      }
      if (value && (value->type == XML_TEXT_NODE))
      {
        if (!strcmp((char*)node->name, "units"))
          e->units = str2units((char *)value->content);
        else if (!strcmp((char*)node->name, "line-weight"))
          e->line_weight = strtod((char *)value->content, NULL);
        else if (!strcmp((char*)node->name, "line-style"))
          e->line_style = strdup((char *)value->content);
        else if (!strcmp((char*)node->name, "fill-style"))
          e->fill_style = strdup((char *)value->content);
        else if (!strcmp((char*)node->name, "dimension"))
          e->dimension = design_dimension_from_xml_node(node);
        else if (!strcmp((char*)node->name, "elliptic"))
          e->elliptic = design_elliptic_from_xml_node(node);
        else if (!strcmp((char*)node->name, "line"))
          e->line = design_line_from_xml_node(node);
        else if (!strcmp((char*)node->name, "point"))
          e->point = design_point_from_xml_node(node);
        else if (!strcmp((char*)node->name, "polyline"))
          e->polyline = design_polyline_from_xml_node(node);
        else if (!strcmp((char*)node->name, "spline"))
          e->spline = design_spline_from_xml_node(node);
        else if (!strcmp((char*)node->name, "text"))
          e->text = design_text_from_xml_node(node);
        else if (!strcmp((char*)node->name, "tolerance"))
          e->tolerance = design_tolerance_from_xml_node(node);
      }
    }
  }

    // Return RETVAL
  return e;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_element_s *design_element_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_element_s *e = NULL;
  color_s *color = NULL;
  design_dimension_s *dimension = NULL;
  design_elliptic_s *elliptic = NULL;
  design_line_s *line = NULL;
  design_point_s *point = NULL;
  design_polyline_s *polyline = NULL;
  design_spline_s *spline = NULL;
  design_text_s *text = NULL;
  design_tolerance_s *tolerance = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<element[^<]*>.*</element>"
                    "|<color[^<]*/>"
                    "|<dimension[^<]*>.*</dimension>"
                    "|<elliptic[^<]*>.*</elliptic>"
                    "|<fill[^<]*>.*</fill>"
                    "|<line[^<]*>.*</line>"
                    "|<point[^<]*>.*</point>"
                    "|<polyline[^<]*>.*</polyline>"
                    "|<spline[^<]*>.*</spline>"
                    "|<text[^<]*>.*</text>"
                    "|<tolerance[^<]*>.*</tolerance>"
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
        if (!strcmp((char *)root->name, "element"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            e = design_element_from_xml_doc(doc);
            if (e) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "color"))
        {
          color = color_from_xml_doc(doc);
          if (color)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "color"))
            {
              if (!e) e = design_element_create();
              design_element_set_color(e, color);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "dimension"))
        {
          if (!e) e = design_element_create();
          if (e)
          {
            dimension = design_dimension_from_xml_doc(doc);
            if (dimension)
            {
              design_element_set_dimension(e, dimension);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "elliptic"))
        {
          if (!e) e = design_element_create();
          if (e)
          {
            elliptic = design_elliptic_from_xml_doc(doc);
            if (elliptic)
            {
              design_element_set_elliptic(e, elliptic);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "line"))
        {
          if (!e) e = design_element_create();
          if (e)
          {
            line = design_line_from_xml_doc(doc);
            if (line)
            {
              design_element_set_line(e, line);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "point"))
        {
          if (!e) e = design_element_create();
          if (e)
          {
            point = design_point_from_xml_doc(doc);
            if (point)
            {
              design_element_set_point(e, point);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "polyline"))
        {
          if (!e) e = design_element_create();
          if (e)
          {
            polyline = design_polyline_from_xml_doc(doc);
            if (polyline)
            {
              design_element_set_polyline(e, polyline);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "spline"))
        {
          if (!e) e = design_element_create();
          if (e)
          {
            spline = design_spline_from_xml_doc(doc);
            if (spline)
            {
              design_element_set_spline(e, spline);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "text"))
        {
          if (!e) e = design_element_create();
          if (e)
          {
            text = design_text_from_xml_doc(doc);
            if (text)
            {
              design_element_set_text(e, text);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "tolerance"))
        {
          if (!e) e = design_element_create();
          if (e)
          {
            tolerance = design_tolerance_from_xml_doc(doc);
            if (tolerance)
            {
              design_element_set_tolerance(e, tolerance);
              doc_list_consume(dl, dl->keep[i]);
            }
          }
        }
        else if (!strcmp((char *)root->name, "defaults"))
        {
          defaults = design_defaults_from_xml_doc(doc);
          if (defaults)
          {
            design_defaults_push(defaults);
            doc_list_consume(dl, dl->keep[i]);
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
  return e;
}

