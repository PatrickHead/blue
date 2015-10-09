/*!
    @file blue-design-elliptic-parms.c

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

    @file blue-design-elliptic-parms.c

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

#include "blue-design-elliptic-parms.h"

static unsigned char errors[blue_design_elliptic_parameter_END
                            - blue_design_elliptic_parameter_BEG];
static unsigned char changed[blue_design_elliptic_parameter_END
                             - blue_design_elliptic_parameter_BEG];

static unsigned char get_error(blue_design_elliptic_parameter_t p);
static void set_error(blue_design_elliptic_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_elliptic_s *blue_design_elliptic_parameter_handler(int argc,
                                                          char** argv,
                                                          design_elliptic_s *e)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "center", 1, 0, blue_design_elliptic_parameter_center },
      { "width", 1, 0, blue_design_elliptic_parameter_width },
      { "height", 1, 0, blue_design_elliptic_parameter_height },
      { "rotation", 1, 0, blue_design_elliptic_parameter_rotation },
      { "start-angle", 1, 0, blue_design_elliptic_parameter_start_angle },
      { "end-angle", 1, 0, blue_design_elliptic_parameter_end_angle },
      { "defaults-xml", 1, 0, blue_design_elliptic_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!e) e = design_elliptic_create();
  if (!e) return NULL;

  blue_design_elliptic_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_elliptic_parameter_center:
        design_elliptic_set_center(e, str2vertex(optarg));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_center);
        break;
      case blue_design_elliptic_parameter_width:
        design_elliptic_set_width(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_width);
        break;
      case blue_design_elliptic_parameter_height:
        design_elliptic_set_height(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_height);
        break;
      case blue_design_elliptic_parameter_rotation:
        design_elliptic_set_rotation(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_rotation);
        break;
      case blue_design_elliptic_parameter_start_angle:
        design_elliptic_set_start_angle(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(
          blue_design_elliptic_parameter_start_angle);
        break;
      case blue_design_elliptic_parameter_end_angle:
        design_elliptic_set_end_angle(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_end_angle);
        break;
      case blue_design_elliptic_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_defaults_xml);
        break;
    }
  }

  blue_design_elliptic_unset_changes();

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

int blue_design_elliptic_check(design_elliptic_s *e)
{
  int i;

    // Sanity check parameters.
  assert(e);

  unset_errors();

  if (e->width < 0.0) set_error(blue_design_elliptic_parameter_width);
  if (e->height < 0.0) set_error(blue_design_elliptic_parameter_height);
  if (e->rotation < 0.0) set_error(blue_design_elliptic_parameter_rotation);
  if (e->start_angle < 0.0) set_error(blue_design_elliptic_parameter_start_angle);
  if (e->end_angle < 0.0) set_error(blue_design_elliptic_parameter_end_angle);

  for (i = blue_design_elliptic_parameter_BEG;
       i < blue_design_elliptic_parameter_END;
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

void blue_design_elliptic_check_error(void)
{
  if (get_error(blue_design_elliptic_parameter_center))
    fprintf(stderr, "Parameter Error; center\n");
  if (get_error(blue_design_elliptic_parameter_width))
    fprintf(stderr, "Parameter Error; width\n");
  if (get_error(blue_design_elliptic_parameter_height))
    fprintf(stderr, "Parameter Error; height\n");
  if (get_error(blue_design_elliptic_parameter_rotation))
    fprintf(stderr, "Parameter Error; rotation\n");
  if (get_error(blue_design_elliptic_parameter_start_angle))
    fprintf(stderr, "Parameter Error; start-angle\n");
  if (get_error(blue_design_elliptic_parameter_end_angle))
    fprintf(stderr, "Parameter Error; end-angle\n");
  if (get_error(blue_design_elliptic_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_elliptic_get_change(blue_design_elliptic_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_elliptic_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_elliptic_set_change(blue_design_elliptic_parameter_t p)
{
  changed[p - blue_design_elliptic_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_elliptic_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_elliptic_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_elliptic_parameter_BEG];
}

static void set_error(blue_design_elliptic_parameter_t p)
{
  errors[p - blue_design_elliptic_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

