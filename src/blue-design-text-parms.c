/*!
    @file blue-design-text-parms.c

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

    @file blue-design-text-parms.c

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

#include "design-defaults-xml.h"

#include "blue-design-text-parms.h"

static unsigned char errors[blue_design_text_parameter_END
                            - blue_design_text_parameter_BEG];
static unsigned char changed[blue_design_text_parameter_END
                             - blue_design_text_parameter_BEG];

static unsigned char get_error(blue_design_text_parameter_t p);
static void set_error(blue_design_text_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_text_s *blue_design_text_parameter_handler(int argc,
                                                  char** argv,
                                                  design_text_s *t)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "type", 1, 0, blue_design_text_parameter__type },
      { "location", 1, 0, blue_design_text_parameter_location },
      { "rotation", 1, 0, blue_design_text_parameter_rotation },
      { "anchor-point", 1, 0, blue_design_text_parameter_anchor_point },
      { "size", 1, 0, blue_design_text_parameter_size },
      { "text", 1, 0, blue_design_text_parameter_text },
      { "defaults-xml", 1, 0, blue_design_text_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!t) t = design_text_create();
  if (!t) return NULL;

  blue_design_text_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_text_parameter__type:
        design_text_set_type(t, str2design_text_type(optarg));
        blue_design_text_set_change(blue_design_text_parameter__type);
        break;
      case blue_design_text_parameter_location:
        design_text_set_location(t, str2vertex(optarg));
        blue_design_text_set_change(blue_design_text_parameter_location);
        break;
      case blue_design_text_parameter_rotation:
        design_text_set_rotation(t, strtod(optarg, NULL));
        blue_design_text_set_change(blue_design_text_parameter_rotation);
        break;
      case blue_design_text_parameter_anchor_point:
        design_text_set_anchor_point(t, str2design_anchor_location_type(optarg));
        blue_design_text_set_change(blue_design_text_parameter_anchor_point);
        break;
      case blue_design_text_parameter_size:
        design_text_set_size(t, strtod(optarg, NULL));
        blue_design_text_set_change(blue_design_text_parameter_size);
        break;
      case blue_design_text_parameter_text:
        design_text_set_text(t, optarg);
        blue_design_text_set_change(blue_design_text_parameter_text);
        break;
      case blue_design_text_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_text_set_change(blue_design_text_parameter_defaults_xml);
        break;
    }
  }

  blue_design_text_unset_changes();

    // Return RETVAL
  return t;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_design_text_check(design_text_s *t)
{
  int i;

    // Sanity check parameters.
  assert(t);

  unset_errors();

  if (t->rotation < 0.0) set_error(blue_design_text_parameter_rotation);
  if (t->size < 0.0) set_error(blue_design_text_parameter_size);

  for (i = blue_design_text_parameter_BEG;
       i < blue_design_text_parameter_END;
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

void blue_design_text_check_error(void)
{
  if (get_error(blue_design_text_parameter__type))
    fprintf(stderr, "Parameter Error; type\n");
  if (get_error(blue_design_text_parameter_location))
    fprintf(stderr, "Parameter Error; location\n");
  if (get_error(blue_design_text_parameter_rotation))
    fprintf(stderr, "Parameter Error; rotation\n");
  if (get_error(blue_design_text_parameter_anchor_point))
    fprintf(stderr, "Parameter Error; anchor_point\n");
  if (get_error(blue_design_text_parameter_size))
    fprintf(stderr, "Parameter Error; size\n");
  if (get_error(blue_design_text_parameter_text))
    fprintf(stderr, "Parameter Error; text\n");
  if (get_error(blue_design_text_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_text_get_change(blue_design_text_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_text_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_text_set_change(blue_design_text_parameter_t p)
{
  changed[p - blue_design_text_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_text_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_text_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_text_parameter_BEG];
}

static void set_error(blue_design_text_parameter_t p)
{
  errors[p - blue_design_text_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

