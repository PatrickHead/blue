/*!
    @file blue-design-dimension-parms.c

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

    @file blue-design-dimension-parms.c

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

#include "design-angular-xml.h"
#include "design-linear-xml.h"
#include "design-radial-xml.h"
#include "design-defaults-xml.h"

#include "blue-design-dimension-parms.h"

static unsigned char errors[blue_design_dimension_parameter_END
                            - blue_design_dimension_parameter_BEG];
static unsigned char changed[blue_design_dimension_parameter_END
                             - blue_design_dimension_parameter_BEG];

static unsigned char get_error(blue_design_dimension_parameter_t p);
static void set_error(blue_design_dimension_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_dimension_s *blue_design_dimension_parameter_handler(int argc,
                                                            char** argv,
                                                            design_dimension_s *d)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "text-size", 1, 0, blue_design_dimension_parameter_text_size },
      { "text-location", 1, 0, blue_design_dimension_parameter_text_location },
      { "precision", 1, 0, blue_design_dimension_parameter_precision },
      { "angular-xml", 1, 0, blue_design_dimension_parameter_angular_xml },
      { "linear-xml", 1, 0, blue_design_dimension_parameter_linear_xml },
      { "radial-xml", 1, 0, blue_design_dimension_parameter_radial_xml },
      { "defaults-xml", 1, 0, blue_design_dimension_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_angular_s *a;
  design_linear_s *l;
  design_radial_s *r;
  design_defaults_s *dfs;
  xmlDocPtr doc;

  if (!d) d = design_dimension_create();
  if (!d) return NULL;

  blue_design_dimension_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_dimension_parameter_text_size:
        design_dimension_set_text_size(d, strtod(optarg, NULL));
        blue_design_dimension_set_change(
          blue_design_dimension_parameter_text_size);
        break;
      case blue_design_dimension_parameter_text_location:
        design_dimension_set_text_location(d, str2vertex(optarg));
        blue_design_dimension_set_change(
          blue_design_dimension_parameter_text_location);
        break;
      case blue_design_dimension_parameter_precision:
        design_dimension_set_precision(d, strtol(optarg, NULL, 10));
        blue_design_dimension_set_change(
           blue_design_dimension_parameter_precision);
        break;
      case blue_design_dimension_parameter_angular_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        a = design_angular_from_xml_doc(doc);
        if (a)
          design_dimension_set_angular(d, a);
        xmlFreeDoc(doc);
        blue_design_dimension_set_change(
           blue_design_dimension_parameter_angular_xml);
        break;
      case blue_design_dimension_parameter_linear_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        l = design_linear_from_xml_doc(doc);
        if (l)
          design_dimension_set_linear(d, l);
        xmlFreeDoc(doc);
        blue_design_dimension_set_change(
           blue_design_dimension_parameter_linear_xml);
        break;
      case blue_design_dimension_parameter_radial_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        r = design_radial_from_xml_doc(doc);
        if (r)
          design_dimension_set_radial(d, r);
        xmlFreeDoc(doc);
        blue_design_dimension_set_change(
           blue_design_dimension_parameter_radial_xml);
        break;
      case blue_design_dimension_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        dfs = design_defaults_from_xml_doc(doc);
        if (dfs) design_defaults_push(dfs);
        xmlFreeDoc(doc);
        blue_design_dimension_set_change(
          blue_design_dimension_parameter_defaults_xml);
        break;
    }
  }

  blue_design_dimension_unset_changes();

    // Return RETVAL
  return d;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_design_dimension_check(design_dimension_s *d)
{
  int i;

    // Sanity check parameters.
  assert(d);

  unset_errors();

  if (d->text_size < 0.0) set_error(blue_design_dimension_parameter_text_size);

  for (i = blue_design_dimension_parameter_BEG;
       i < blue_design_dimension_parameter_END;
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

void blue_design_dimension_check_error(void)
{
  if (get_error(blue_design_dimension_parameter_text_size))
    fprintf(stderr, "Parameter Error; text-size\n");
  if (get_error(blue_design_dimension_parameter_text_location))
    fprintf(stderr, "Parameter Error; text-location\n");
  if (get_error(blue_design_dimension_parameter_angular_xml))
    fprintf(stderr, "Parameter Error; angular-xml\n");
  if (get_error(blue_design_dimension_parameter_linear_xml))
    fprintf(stderr, "Parameter Error; linear-xml\n");
  if (get_error(blue_design_dimension_parameter_radial_xml))
    fprintf(stderr, "Parameter Error; radial-xml\n");
  if (get_error(blue_design_dimension_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_dimension_get_change(
  blue_design_dimension_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_dimension_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_dimension_set_change(blue_design_dimension_parameter_t p)
{
  changed[p - blue_design_dimension_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_dimension_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_dimension_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_dimension_parameter_BEG];
}

static void set_error(blue_design_dimension_parameter_t p)
{
  errors[p - blue_design_dimension_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

