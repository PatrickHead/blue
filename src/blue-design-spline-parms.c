/*!
    @file blue-design-spline-parms.c

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

    @file blue-design-spline-parms.c

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

#include "vertices-xml.h"
#include "design-defaults-xml.h"

#include "blue-design-spline-parms.h"

static unsigned char errors[blue_design_spline_parameter_END
                            - blue_design_spline_parameter_BEG];
static unsigned char changed[blue_design_spline_parameter_END
                             - blue_design_spline_parameter_BEG];

static unsigned char get_error(blue_design_spline_parameter_t p);
static void set_error(blue_design_spline_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_spline_s *blue_design_spline_parameter_handler(int argc,
                                                      char** argv,
                                                      design_spline_s *s)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "vertices-xml", 1, 0, blue_design_spline_parameter_vertices_xml },
      { "defaults-xml", 1, 0, blue_design_spline_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  vertices_s *v;
  xmlDocPtr doc;

  if (!s) s = design_spline_create();
  if (!s) return NULL;

  blue_design_spline_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_spline_parameter_vertices_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        v = vertices_from_xml_doc(doc);
        if (v) design_spline_set_vertices(s, v);
        xmlFreeDoc(doc);
        blue_design_spline_set_change(blue_design_spline_parameter_vertices_xml);
        break;
      case blue_design_spline_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_spline_set_change(blue_design_spline_parameter_defaults_xml);
        break;
      default: break;
    }
  }

  blue_design_spline_unset_changes();

    // Return RETVAL
  return s;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_design_spline_check(design_spline_s *s)
{
  int i;

    // Sanity check parameters.
  assert(s);

  unset_errors();

  for (i = blue_design_spline_parameter_BEG;
       i < blue_design_spline_parameter_END;
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

void blue_design_spline_check_error(void)
{
  if (get_error(blue_design_spline_parameter_vertices_xml))
    fprintf(stderr, "Parameter Error; vertices-xml\n");
  if (get_error(blue_design_spline_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_spline_get_change(blue_design_spline_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_spline_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_spline_set_change(blue_design_spline_parameter_t p)
{
  changed[p - blue_design_spline_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_spline_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_spline_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_spline_parameter_BEG];
}

static void set_error(blue_design_spline_parameter_t p)
{
  errors[p - blue_design_spline_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

