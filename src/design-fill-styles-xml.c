/*!
    @file design-fill-styles-xml.c

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

    @file design-fill-styles-xml.c

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
#include "design-fill-styles-xml.h"

#define MAX_SN 40

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlDocPtr design_fill_styles_to_xml_doc(design_fill_styles_s *fss)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root = NULL;

    // Sanity check parameters.
  assert(fss);

  doc = xmlNewDoc(BAD_CAST "1.0");

  root = design_fill_styles_to_xml_node(fss);

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

xmlNodePtr design_fill_styles_to_xml_node(design_fill_styles_s *fss)
{
  xmlNodePtr fssn;
  xmlNodePtr fsn;
  design_fill_style_s *fs;

    // Sanity check parameters.
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

    // Return RETVAL
  return fssn;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

xmlNodePtr design_fill_styles_root_node(xmlDocPtr doc)
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

design_fill_styles_s *design_fill_styles_from_xml_doc(xmlDocPtr doc)
{
  xmlNodePtr root;

    // Sanity check parameters.
  assert(doc);

  root = design_fill_styles_root_node(doc);

    // Return RETVAL
  return design_fill_styles_from_xml_node(root);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_styles_s *design_fill_styles_from_xml_node(xmlNodePtr node)
{
  xmlNodePtr value;
  design_fill_styles_s *fss;
  design_fill_style_s *fs;

    // Sanity check parameters.
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

    // Return RETVAL
  return fss;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

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

  dl = doc_list_create(infile,
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

    // Return RETVAL
  return fss;
}

