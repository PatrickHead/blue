/*!
    @file blue-design-element-parms.c

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

    @file blue-design-element-parms.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

  // Project related headers

#include "units.h"
#include "color-xml.h"
#include "design-dimension-xml.h"
#include "design-elliptic-xml.h"
#include "design-line-xml.h"
#include "design-point-xml.h"
#include "design-polyline-xml.h"
#include "design-spline-xml.h"
#include "design-text-xml.h"
#include "design-tolerance-xml.h"
#include "design-defaults-xml.h"

#include "blue-design-element-parms.h"

static unsigned char errors[blue_design_element_parameter_END
                            - blue_design_element_parameter_BEG];
static unsigned char changed[blue_design_element_parameter_END
                             - blue_design_element_parameter_BEG];

static unsigned char get_error(blue_design_element_parameter_t p);
static void set_error(blue_design_element_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_element_s *blue_design_element_parameter_handler(int argc,
                                                        char** argv,
                                                        design_element_s *e)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "id", 1, 0, blue_design_element_parameter_id },
      { "units", 1, 0, blue_design_element_parameter_units },
      { "line-weight", 1, 0, blue_design_element_parameter_line_weight },
      { "line-style", 1, 0, blue_design_element_parameter_line_style },
      { "fill-style", 1, 0, blue_design_element_parameter_fill_style },
      { "color-xml", 1, 0, blue_design_element_parameter_color_xml },
      { "dimension-xml", 1, 0, blue_design_element_parameter_dimension_xml },
      { "elliptic-xml", 1, 0, blue_design_element_parameter_elliptic_xml },
      { "fill-xml", 1, 0, blue_design_element_parameter_fill_xml },
      { "line-xml", 1, 0, blue_design_element_parameter_line_xml },
      { "point-xml", 1, 0, blue_design_element_parameter_point_xml },
      { "polyline-xml", 1, 0, blue_design_element_parameter_polyline_xml },
      { "spline-xml", 1, 0, blue_design_element_parameter_spline_xml },
      { "text-xml", 1, 0, blue_design_element_parameter_text_xml },
      { "tolerance-xml", 1, 0, blue_design_element_parameter_tolerance_xml },
      { "defaults-xml", 1, 0, blue_design_element_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  color_s *color;
  design_dimension_s *dimension;
  design_elliptic_s *elliptic;
  design_line_s *line;
  design_point_s *point;
  design_polyline_s *polyline;
  design_spline_s *spline;
  design_text_s *text;
  design_tolerance_s *tolerance;
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!e) e = design_element_create();
  if (!e) return NULL;

  blue_design_element_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_element_parameter_id:
        design_element_set_id(e, strtol(optarg, NULL, 10));
        blue_design_element_set_change(blue_design_element_parameter_id);
        break;
      case blue_design_element_parameter_units:
        design_element_set_units(e, str2units(optarg));
        blue_design_element_set_change(blue_design_element_parameter_units);
        break;
      case blue_design_element_parameter_line_weight:
        design_element_set_line_weight(e, strtod(optarg, NULL));
        blue_design_element_set_change(blue_design_element_parameter_line_weight);
        break;
      case blue_design_element_parameter_line_style:
        design_element_set_line_style(e, optarg);
        blue_design_element_set_change(blue_design_element_parameter_line_style);
        break;
      case blue_design_element_parameter_fill_style:
        design_element_set_fill_style(e, optarg);
        blue_design_element_set_change(blue_design_element_parameter_fill_style);
        break;
      case blue_design_element_parameter_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          design_element_set_color(e, color);
        xmlFreeDoc(doc);
        blue_design_element_set_change(
          blue_design_element_parameter_color_xml);
        break;
      case blue_design_element_parameter_dimension_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        dimension = design_dimension_from_xml_doc(doc);
        if (dimension)
          design_element_set_dimension(e, dimension);
        xmlFreeDoc(doc);
        blue_design_element_set_change(
          blue_design_element_parameter_dimension_xml);
        break;
      case blue_design_element_parameter_elliptic_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        elliptic = design_elliptic_from_xml_doc(doc);
        if (elliptic)
          design_element_set_elliptic(e, elliptic);
        xmlFreeDoc(doc);
        blue_design_element_set_change(
          blue_design_element_parameter_elliptic_xml);
        break;
      case blue_design_element_parameter_line_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        line = design_line_from_xml_doc(doc);
        if (line)
          design_element_set_line(e, line);
        xmlFreeDoc(doc);
        blue_design_element_set_change(blue_design_element_parameter_line_xml);
        break;
      case blue_design_element_parameter_point_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        point = design_point_from_xml_doc(doc);
        if (point)
          design_element_set_point(e, point);
        xmlFreeDoc(doc);
        blue_design_element_set_change(blue_design_element_parameter_point_xml);
        break;
      case blue_design_element_parameter_polyline_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        polyline = design_polyline_from_xml_doc(doc);
        if (polyline)
          design_element_set_polyline(e, polyline);
        xmlFreeDoc(doc);
        blue_design_element_set_change(
          blue_design_element_parameter_polyline_xml);
        break;
      case blue_design_element_parameter_spline_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        spline = design_spline_from_xml_doc(doc);
        if (spline)
          design_element_set_spline(e, spline);
        xmlFreeDoc(doc);
        blue_design_element_set_change(blue_design_element_parameter_spline_xml);
        break;
      case blue_design_element_parameter_text_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        text = design_text_from_xml_doc(doc);
        if (text)
          design_element_set_text(e, text);
        xmlFreeDoc(doc);
        blue_design_element_set_change(blue_design_element_parameter_text_xml);
        break;
      case blue_design_element_parameter_tolerance_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        tolerance = design_tolerance_from_xml_doc(doc);
        if (tolerance)
          design_element_set_tolerance(e, tolerance);
        xmlFreeDoc(doc);
        blue_design_element_set_change(
          blue_design_element_parameter_tolerance_xml);
        break;
      case blue_design_element_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_element_set_change(blue_design_element_parameter_defaults_xml);
        break;
      default: break;
    }
  }

  blue_design_element_unset_changes();

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

int blue_design_element_check(design_element_s *e)
{
  int i;

    // Sanity check parameters.
  assert(e);

  unset_errors();

  if (e->id < 0) set_error(blue_design_element_parameter_id);
  if (e->line_weight < 0.0) set_error(blue_design_element_parameter_line_weight);

  for (i = blue_design_element_parameter_BEG;
       i < blue_design_element_parameter_END;
       i++)
    if (get_error(i))
        // Return RETVAL
  return 1;

    // Return RETVAL
  return 0;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_element_check_error(void)
{
  if (get_error(blue_design_element_parameter_id))
    fprintf(stderr, "Parameter Error; id\n");
  if (get_error(blue_design_element_parameter_units))
    fprintf(stderr, "Parameter Error; units\n");
  if (get_error(blue_design_element_parameter_line_weight))
    fprintf(stderr, "Parameter Error; line-weight\n");
  if (get_error(blue_design_element_parameter_line_style))
    fprintf(stderr, "Parameter Error; line-style\n");
  if (get_error(blue_design_element_parameter_fill_style))
    fprintf(stderr, "Parameter Error; fill-style\n");
  if (get_error(blue_design_element_parameter_color_xml))
    fprintf(stderr, "Parameter Error; color-xml\n");
  if (get_error(blue_design_element_parameter_dimension_xml))
    fprintf(stderr, "Parameter Error; dimension-xml\n");
  if (get_error(blue_design_element_parameter_elliptic_xml))
    fprintf(stderr, "Parameter Error; elliptic-xml\n");
  if (get_error(blue_design_element_parameter_fill_xml))
    fprintf(stderr, "Parameter Error; fill-xml\n");
  if (get_error(blue_design_element_parameter_line_xml))
    fprintf(stderr, "Parameter Error; line-xml\n");
  if (get_error(blue_design_element_parameter_point_xml))
    fprintf(stderr, "Parameter Error; point-xml\n");
  if (get_error(blue_design_element_parameter_polyline_xml))
    fprintf(stderr, "Parameter Error; polyline-xml\n");
  if (get_error(blue_design_element_parameter_spline_xml))
    fprintf(stderr, "Parameter Error; spline-xml\n");
  if (get_error(blue_design_element_parameter_text_xml))
    fprintf(stderr, "Parameter Error; text-xml\n");
  if (get_error(blue_design_element_parameter_tolerance_xml))
    fprintf(stderr, "Parameter Error; tolerance-xml\n");
  if (get_error(blue_design_element_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_element_get_change(blue_design_element_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_element_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_element_set_change(blue_design_element_parameter_t p)
{
  changed[p - blue_design_element_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_element_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_element_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_element_parameter_BEG];
}

static void set_error(blue_design_element_parameter_t p)
{
  errors[p - blue_design_element_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

