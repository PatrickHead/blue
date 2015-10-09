/*!
    @file blue-design-tolerance-parms.c

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

    @file blue-design-tolerance-parms.c

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

#include "blue-design-tolerance-parms.h"

static unsigned char errors[blue_design_tolerance_parameter_END
                            - blue_design_tolerance_parameter_BEG];
static unsigned char changed[blue_design_tolerance_parameter_END
                             - blue_design_tolerance_parameter_BEG];

static unsigned char get_error(blue_design_tolerance_parameter_t p);
static void set_error(blue_design_tolerance_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_tolerance_s *blue_design_tolerance_parameter_handler(int argc,
                                                            char** argv,
                                                            design_tolerance_s *t)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "location", 1, 0, blue_design_tolerance_parameter_location },
      { "text-size", 1, 0, blue_design_tolerance_parameter_text_size },
      { "plus", 1, 0, blue_design_tolerance_parameter_plus },
      { "minus", 1, 0, blue_design_tolerance_parameter_minus },
      { "precision", 1, 0, blue_design_tolerance_parameter_precision },
      { "defaults-xml", 1, 0, blue_design_tolerance_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!t) t = design_tolerance_create();
  if (!t) return NULL;

  blue_design_tolerance_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_tolerance_parameter_location:
        design_tolerance_set_location(t, str2vertex(optarg));
        blue_design_tolerance_set_change(
          blue_design_tolerance_parameter_location);
        break;
      case blue_design_tolerance_parameter_text_size:
        design_tolerance_set_text_size(t, strtod(optarg, NULL));
        blue_design_tolerance_set_change(
          blue_design_tolerance_parameter_text_size);
        break;
      case blue_design_tolerance_parameter_plus:
        design_tolerance_set_plus(t, strtod(optarg, NULL));
        blue_design_tolerance_set_change(blue_design_tolerance_parameter_plus);
        break;
      case blue_design_tolerance_parameter_minus:
        design_tolerance_set_minus(t, strtod(optarg, NULL));
        blue_design_tolerance_set_change(blue_design_tolerance_parameter_minus);
        break;
      case blue_design_tolerance_parameter_precision:
        design_tolerance_set_precision(t, strtol(optarg, NULL, 10));
        blue_design_tolerance_set_change(
          blue_design_tolerance_parameter_precision);
        break;
      case blue_design_tolerance_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_tolerance_set_change(blue_design_tolerance_parameter_defaults_xml);
        break;
    }
  }

  blue_design_tolerance_unset_changes();

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

int blue_design_tolerance_check(design_tolerance_s *t)
{
  int i;

    // Sanity check parameters.
  assert(t);

  unset_errors();

  if (t->text_size < 0.0) set_error(blue_design_tolerance_parameter_text_size);
  if (t->plus < 0.0) set_error(blue_design_tolerance_parameter_plus);
  if (t->minus < 0.0) set_error(blue_design_tolerance_parameter_minus);
  if (t->precision < 0) set_error(blue_design_tolerance_parameter_precision);

  for (i = blue_design_tolerance_parameter_BEG;
       i < blue_design_tolerance_parameter_END;
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

void blue_design_tolerance_check_error(void)
{
  if (get_error(blue_design_tolerance_parameter_location))
    fprintf(stderr, "Parameter Error; location\n");
  if (get_error(blue_design_tolerance_parameter_text_size))
    fprintf(stderr, "Parameter Error; text-size\n");
  if (get_error(blue_design_tolerance_parameter_plus))
    fprintf(stderr, "Parameter Error; plus\n");
  if (get_error(blue_design_tolerance_parameter_minus))
    fprintf(stderr, "Parameter Error; minus\n");
  if (get_error(blue_design_tolerance_parameter_precision))
    fprintf(stderr, "Parameter Error; precision\n");
  if (get_error(blue_design_tolerance_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_tolerance_get_change(blue_design_tolerance_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_tolerance_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_tolerance_set_change(blue_design_tolerance_parameter_t p)
{
  changed[p - blue_design_tolerance_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_tolerance_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_tolerance_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_tolerance_parameter_BEG];
}

static void set_error(blue_design_tolerance_parameter_t p)
{
  errors[p - blue_design_tolerance_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

