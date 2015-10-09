/*!
    @file design-point-xml.c

    @brief SOURCE_BRIEF

    @timestamp Fri, 09 Oct 2015 03:31:15 +0000

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

    @file design-point-xml.c

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
#include "design-point-xml.h"

#define MAX_SN 40

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlDocPtr design_point_to_xml_doc(design_point_s *p)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

    // Sanity check parameters.
  assert(p);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_point_to_xml_node(p);

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

xmlNodePtr design_point_to_xml_node(design_point_s *p)
{
  xmlNodePtr n = NULL;
  xmlNodePtr vn = NULL;

    // Sanity check parameters.
  assert(p);

  n = xmlNewNode(NULL, BAD_CAST "point");
  if (!n) return NULL;

  vn = vertex_to_xml_node(p->location);
  if (vn)
  {
    xmlAddChild(n, xmlCopyNode(vn, 1));
    xmlFreeNode(vn);
  }

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

xmlNodePtr design_point_root_node(xmlDocPtr doc)
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

design_point_s *design_point_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

    // Sanity check parameters.
  assert(doc);

  root = design_point_root_node(doc);

    // Return RETVAL
  return design_point_from_xml_node(root);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_point_s *design_point_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_point_s *p;

    // Sanity check parameters.
  assert(node);

  if (strcmp((char*)node->name, "point")) return NULL;

  p = design_point_create();
  if (!p) return NULL;

  for (node = node->children; node; node = node->next)
  {
    if (node->type == XML_ELEMENT_NODE)
    {
      value = node->children;
      if (!value)
      {
        if (!strcmp((char*)node->name, "vertex"))
        {
          if (!strcmp((char *)xmlGetProp(node, BAD_CAST "tag"), "location"))
            p->location = vertex_from_xml_node(node);
        }
      }
    }
  }

    // Return RETVAL
  return p;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_point_s *design_point_sieve(FILE *infile, FILE *outfile)
{
  doc_list_s *dl;
  design_point_s *p = NULL;
  vertex_s *vertex = NULL;
  design_defaults_s *defaults = NULL;
  int i;
  xmlDocPtr doc;
  xmlNodePtr root;
  int have_one = 0;

  if (!infile) return NULL;

  dl = doc_list_create(infile,
                    "<?xml[^<]*?>",
                    "<point[^<]*>.*</point>"
                    "|<vertex[^<]*/>"
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
        if (!strcmp((char *)root->name, "point"))
        {
          if (!have_one &&
              (sieve_get_process_mode() == sieve_process_mode_type_edit))
          {
            have_one = 1;
            p = design_point_from_xml_doc(doc);
            if (p) doc_list_consume(dl, dl->keep[i]);
          }
        }
        else if (!strcmp((char *)root->name, "vertex"))
        {
          vertex = vertex_from_xml_doc(doc);
          if (vertex)
          {
            if (!strcmp((char *)xmlGetProp(root, BAD_CAST "tag"), "location"))
            {
              if (!p) p = design_point_create();
              if (p->location) vertex_destroy(p->location);
              p->location = vertex;
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
  return p;
}

