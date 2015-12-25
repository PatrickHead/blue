/*!
    @file blue-design-fill-style-parms.c

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

    @file blue-design-fill-style-parms.c

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

#include "blue-design-fill-style-parms.h"

static unsigned char errors[blue_design_fill_style_parameter_END
                            - blue_design_fill_style_parameter_BEG];
static unsigned char changed[blue_design_fill_style_parameter_END
                             - blue_design_fill_style_parameter_BEG];

static unsigned char get_error(blue_design_fill_style_parameter_t p);
static void set_error(blue_design_fill_style_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_style_s *blue_design_fill_style_parameter_handler(int argc,
                                                  char** argv,
                                                  design_fill_style_s *fs)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "name", 1, 0, blue_design_fill_style_parameter_name },
      { "type", 1, 0, blue_design_fill_style_parameter_TYPE },
      { "line-weight", 1, 0, blue_design_fill_style_parameter_line_weight },
      { "line-style", 1, 0, blue_design_fill_style_parameter_line_style },
      { "background-color-xml",
        1,
        0,
        blue_design_fill_style_parameter_background_color_xml
      },
      { "pattern-color-xml",
        1,
        0,
        blue_design_fill_style_parameter_pattern_color_xml
      },
      { "angle1", 1, 0, blue_design_fill_style_parameter_angle1 },
      { "spacing1", 1, 0, blue_design_fill_style_parameter_spacing1 },
      { "angle2", 1, 0, blue_design_fill_style_parameter_angle2 },
      { "spacing1", 1, 0, blue_design_fill_style_parameter_spacing1 },
      { "source", 1, 0, blue_design_fill_style_parameter_source },
      { 0, 0, 0, 0 }
    };
  color_s *color;
  xmlDocPtr doc;

  if (!fs) fs = design_fill_style_create();
  if (!fs) return NULL;

  blue_design_fill_style_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_fill_style_parameter_name:
        design_fill_style_set_name(fs, optarg);
        blue_design_fill_style_set_change(blue_design_fill_style_parameter_name);
        break;
      case blue_design_fill_style_parameter_TYPE:
        design_fill_style_set_type(fs, str2design_fill_style_type(optarg));
        blue_design_fill_style_set_change(blue_design_fill_style_parameter_TYPE);
        break;
      case blue_design_fill_style_parameter_line_weight:
        design_fill_style_set_line_weight(fs, strtod(optarg, NULL));
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_line_style);
        break;
      case blue_design_fill_style_parameter_line_style:
        design_fill_style_set_line_style(fs, optarg);
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_line_style);
        break;
      case blue_design_fill_style_parameter_background_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          design_fill_style_set_background_color(fs, color);
        xmlFreeDoc(doc);
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_background_color_xml);
        break;
      case blue_design_fill_style_parameter_pattern_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          design_fill_style_set_pattern_color(fs, color);
        xmlFreeDoc(doc);
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_pattern_color_xml);
        break;
      case blue_design_fill_style_parameter_angle1:
        design_fill_style_set_angle1(fs, strtod(optarg, NULL));
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_angle1);
        break;
      case blue_design_fill_style_parameter_spacing1:
        design_fill_style_set_spacing1(fs, strtod(optarg, NULL));
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_spacing1);
        break;
      case blue_design_fill_style_parameter_angle2:
        design_fill_style_set_angle2(fs, strtod(optarg, NULL));
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_angle2);
        break;
      case blue_design_fill_style_parameter_spacing2:
        design_fill_style_set_spacing2(fs, strtod(optarg, NULL));
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_spacing2);
        break;
      case blue_design_fill_style_parameter_source:
        design_fill_style_set_source(fs, optarg);
        blue_design_fill_style_set_change(
          blue_design_fill_style_parameter_source);
        break;
      default: break;
    }
  }

  blue_design_fill_style_unset_changes();

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

int blue_design_fill_style_check(design_fill_style_s *fs)
{
  int i;

    // Sanity check parameters.
  assert(fs);

  unset_errors();

  if (fs->line_weight < 0.0)
    set_error(blue_design_fill_style_parameter_line_weight);
  if (fs->angle1 < 0.0 || fs->angle1 > 90.0)
    set_error(blue_design_fill_style_parameter_angle1);
  if (fs->spacing1 < 0.0)
    set_error(blue_design_fill_style_parameter_spacing1);
  if (fs->angle2 < 0.0 || fs->angle2 > 90.0)
    set_error(blue_design_fill_style_parameter_angle2);
  if (fs->spacing2 < 0.0)
    set_error(blue_design_fill_style_parameter_spacing2);

  for (i = blue_design_fill_style_parameter_BEG;
       i < blue_design_fill_style_parameter_END;
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

void blue_design_fill_style_check_error(void)
{
  if (get_error(blue_design_fill_style_parameter_name))
    fprintf(stderr, "Parameter Error; name\n");
  if (get_error(blue_design_fill_style_parameter_TYPE))
    fprintf(stderr, "Parameter Error; type\n");
  if (get_error(blue_design_fill_style_parameter_line_weight))
    fprintf(stderr, "Parameter Error; line-weight\n");
  if (get_error(blue_design_fill_style_parameter_line_style))
    fprintf(stderr, "Parameter Error; line-style\n");
  if (get_error(blue_design_fill_style_parameter_background_color_xml))
    fprintf(stderr, "Parameter Error; background-color-xml\n");
  if (get_error(blue_design_fill_style_parameter_pattern_color_xml))
    fprintf(stderr, "Parameter Error; pattern-color-xml\n");
  if (get_error(blue_design_fill_style_parameter_angle1))
    fprintf(stderr, "Parameter Error; angle1\n");
  if (get_error(blue_design_fill_style_parameter_spacing1))
    fprintf(stderr, "Parameter Error; spacing1\n");
  if (get_error(blue_design_fill_style_parameter_angle2))
    fprintf(stderr, "Parameter Error; angle2\n");
  if (get_error(blue_design_fill_style_parameter_spacing2))
    fprintf(stderr, "Parameter Error; spacing2\n");
  if (get_error(blue_design_fill_style_parameter_source))
    fprintf(stderr, "Parameter Error; source\n");
}

unsigned char blue_design_fill_style_get_change(blue_design_fill_style_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_fill_style_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_fill_style_set_change(blue_design_fill_style_parameter_t p)
{
  changed[p - blue_design_fill_style_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_fill_style_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_fill_style_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_fill_style_parameter_BEG];
}

static void set_error(blue_design_fill_style_parameter_t p)
{
  errors[p - blue_design_fill_style_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

