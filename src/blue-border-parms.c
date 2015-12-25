/*!
    @file blue-border-parms.c

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

    @file blue-border-parms.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

  // Project related headers

#include "margins-xml.h"
#include "color-xml.h"

#include "blue-border-parms.h"

static unsigned char errors[blue_border_parameter_END - blue_border_parameter_BEG];
static unsigned char changed[blue_border_parameter_END - blue_border_parameter_BEG];

static unsigned char get_error(blue_border_parameter_t p);
static void set_error(blue_border_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

border_s *blue_border_parameter_handler(int argc, char** argv, border_s *b)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "units", 1, 0, blue_border_parameter_units },
      { "line-width", 1, 0, blue_border_parameter_line_width },
      { "background-color-xml",
         1,
         0,
         blue_border_parameter_background_color_xml },
      { "line-color-xml", 1, 0, blue_border_parameter_line_color_xml },
      { "margins-xml", 1, 0, blue_border_parameter_margins_xml },
      { 0, 0, 0, 0 }
    };
  xmlDocPtr doc;
  margins_s *m;
  color_s *color;

  if (!b) b = border_create();
  if (!b) return NULL;

  blue_border_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_border_parameter_units:
        border_set_units(b, str2units(optarg));
        margins_set_units(b->margins, str2units(optarg));
        blue_border_set_change(blue_border_parameter_units);
        break;
      case blue_border_parameter_line_width:
        border_set_line_width(b, strtod(optarg, NULL));
        blue_border_set_change(blue_border_parameter_line_width);
        break;
      case blue_border_parameter_background_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          border_set_background_color(b, color);
        blue_border_set_change(blue_border_parameter_background_color_xml);
        xmlFreeDoc(doc);
        break;
      case blue_border_parameter_line_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          border_set_line_color(b, color);
        blue_border_set_change(blue_border_parameter_line_color_xml);
        xmlFreeDoc(doc);
        break;
      case blue_border_parameter_margins_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        m = margins_from_xml_doc(doc);
        if (m)
          border_set_margins(b, m);
        blue_border_set_change(blue_border_parameter_margins_xml);
        xmlFreeDoc(doc);
        break;
    }
  }

  blue_border_unset_changes();

    // Return RETVAL
  return b;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_border_check(border_s *b)
{
  int i;

    // Sanity check parameters.
  assert(b);

  unset_errors();

  if (b->line_width < 0.0) set_error(blue_border_parameter_line_width);

  for (i = blue_border_parameter_BEG; i < blue_border_parameter_END; i++)
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

void blue_border_check_error(void)
{
  if (get_error(blue_border_parameter_units))
    fprintf(stderr, "Parameter Error; units\n");
  if (get_error(blue_border_parameter_line_width))
    fprintf(stderr, "Parameter Error; line-width\n");
  if (get_error(blue_border_parameter_background_color_xml))
    fprintf(stderr, "Parameter Error; background-color-xml\n");
  if (get_error(blue_border_parameter_line_color_xml))
    fprintf(stderr, "Parameter Error; line-color-xml\n");
  if (get_error(blue_border_parameter_margins_xml))
    fprintf(stderr, "Parameter Error; margins-xml\n");
}

unsigned char blue_border_get_change(blue_border_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_border_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_border_set_change(blue_border_parameter_t p)
{
  changed[p - blue_border_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_border_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_border_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_border_parameter_BEG];
}

static void set_error(blue_border_parameter_t p)
{
  errors[p - blue_border_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

