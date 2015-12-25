/*!
    @file blue-design-radial-parms.c

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

    @file blue-design-radial-parms.c

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

#include "blue-design-radial-parms.h"

static unsigned char errors[blue_design_radial_parameter_END - blue_design_radial_parameter_BEG];
static unsigned char changed[blue_design_radial_parameter_END - blue_design_radial_parameter_BEG];

static unsigned char get_error(blue_design_radial_parameter_t p);
static void set_error(blue_design_radial_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_radial_s *blue_design_radial_parameter_handler(int argc,
                                                      char** argv,
                                                      design_radial_s *r)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "type", 1, 0, blue_design_radial_parameter__type },
      { "center", 1, 0, blue_design_radial_parameter_center },
      { "major", 1, 0, blue_design_radial_parameter_major },
      { "minor", 1, 0, blue_design_radial_parameter_minor },
      { "angle", 1, 0, blue_design_radial_parameter_angle },
      { "leader", 1, 0, blue_design_radial_parameter_leader },
      { "defaults-xml", 1, 0, blue_design_radial_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!r) r = design_radial_create();
  if (!r) return NULL;

  blue_design_radial_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_radial_parameter__type:
        design_radial_set_type(r, str2design_radial_type(optarg));
        blue_design_radial_set_change(blue_design_radial_parameter_angle);
        break;
      case blue_design_radial_parameter_center:
        design_radial_set_center(r, str2vertex(optarg));
        blue_design_radial_set_change(blue_design_radial_parameter_center);
        break;
      case blue_design_radial_parameter_major:
        design_radial_set_major(r, strtod(optarg, NULL));
        blue_design_radial_set_change(blue_design_radial_parameter_major);
        break;
      case blue_design_radial_parameter_minor:
        design_radial_set_minor(r, strtod(optarg, NULL));
        blue_design_radial_set_change(blue_design_radial_parameter_minor);
        break;
      case blue_design_radial_parameter_angle:
        design_radial_set_angle(r, strtod(optarg, NULL));
        blue_design_radial_set_change(blue_design_radial_parameter_angle);
        break;
      case blue_design_radial_parameter_leader:
        design_radial_set_leader(r, strtod(optarg, NULL));
        blue_design_radial_set_change(blue_design_radial_parameter_leader);
        break;
      case blue_design_radial_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_radial_set_change(blue_design_radial_parameter_defaults_xml);
        break;
    }
  }

  blue_design_radial_unset_changes();

    // Return RETVAL
  return r;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_design_radial_check(design_radial_s *r)
{
  int i;

    // Sanity check parameters.
  assert(r);

  unset_errors();

  if (r->major < 0.0) set_error(blue_design_radial_parameter_major);
  if (r->minor < 0.0) set_error(blue_design_radial_parameter_minor);
  if (r->angle < 0.0) set_error(blue_design_radial_parameter_angle);
  if (r->leader < 0.0) set_error(blue_design_radial_parameter_leader);

  for (i = blue_design_radial_parameter_BEG;
       i < blue_design_radial_parameter_END;
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

void blue_design_radial_check_error(void)
{
  if (get_error(blue_design_radial_parameter__type))
    fprintf(stderr, "Parameter Error; type\n");
  if (get_error(blue_design_radial_parameter_center))
    fprintf(stderr, "Parameter Error; center\n");
  if (get_error(blue_design_radial_parameter_major))
    fprintf(stderr, "Parameter Error; major\n");
  if (get_error(blue_design_radial_parameter_minor))
    fprintf(stderr, "Parameter Error; minor\n");
  if (get_error(blue_design_radial_parameter_angle))
    fprintf(stderr, "Parameter Error; angle\n");
  if (get_error(blue_design_radial_parameter_leader))
    fprintf(stderr, "Parameter Error; leader\n");
  if (get_error(blue_design_radial_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_radial_get_change(blue_design_radial_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_radial_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_radial_set_change(blue_design_radial_parameter_t p)
{
  changed[p - blue_design_radial_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_radial_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_radial_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_radial_parameter_BEG];
}

static void set_error(blue_design_radial_parameter_t p)
{
  errors[p - blue_design_radial_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

