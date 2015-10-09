/*!
    @file blue-design-layer-parms.c

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

    @file blue-design-layer-parms.c

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

#include "design-defaults-xml.h"
#include "design-elements-xml.h"

#include "blue-design-layer-parms.h"

static unsigned char errors[blue_design_layer_parameter_END
                            - blue_design_layer_parameter_BEG];
static unsigned char changed[blue_design_layer_parameter_END
                             - blue_design_layer_parameter_BEG];

static unsigned char get_error(blue_design_layer_parameter_t p);
static void set_error(blue_design_layer_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_layer_s *blue_design_layer_parameter_handler(int argc,
                                                    char** argv,
                                                    design_layer_s *l)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "id", 1, 0, blue_design_layer_parameter_id },
      { "name", 1, 0, blue_design_layer_parameter_name },
      { "visibility", 1, 0, blue_design_layer_parameter_visibility },
      { "defaults-xml", 1, 0, blue_design_layer_parameter_defaults_xml },
      { "elements-xml", 1, 0, blue_design_layer_parameter_elements_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  design_elements_s *es;
  xmlDocPtr doc;

  if (!l) l = design_layer_create();
  if (!l) return NULL;

  blue_design_layer_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_layer_parameter_id:
        design_layer_set_id(l, strtol(optarg, NULL, 10));
        blue_design_layer_set_change(blue_design_layer_parameter_id);
        break;
      case blue_design_layer_parameter_name:
        design_layer_set_name(l, optarg);
        blue_design_layer_set_change(blue_design_layer_parameter_name);
        break;
      case blue_design_layer_parameter_visibility:
        design_layer_set_visibility(l, str2design_visibility_type(optarg));
        blue_design_layer_set_change(blue_design_layer_parameter_visibility);
        break;
      case blue_design_layer_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d)
          design_layer_set_defaults(l, d);
        xmlFreeDoc(doc);
        blue_design_layer_set_change(blue_design_layer_parameter_defaults_xml);
        break;
      case blue_design_layer_parameter_elements_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        es = design_elements_from_xml_doc(doc);
        if (es)
          design_layer_set_elements(l, es);
        xmlFreeDoc(doc);
        blue_design_layer_set_change(blue_design_layer_parameter_elements_xml);
        break;
      default: break;
    }
  }

  blue_design_layer_unset_changes();

    // Return RETVAL
  return l;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_design_layer_check(design_layer_s *l)
{
  int i;

    // Sanity check parameters.
  assert(l);

  unset_errors();

  if (l->id < 0) set_error(blue_design_layer_parameter_id);

  for (i = blue_design_layer_parameter_BEG;
       i < blue_design_layer_parameter_END;
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

void blue_design_layer_check_error(void)
{
  if (get_error(blue_design_layer_parameter_id))
    fprintf(stderr, "Parameter Error; id\n");
  if (get_error(blue_design_layer_parameter_name))
    fprintf(stderr, "Parameter Error; name\n");
  if (get_error(blue_design_layer_parameter_visibility))
    fprintf(stderr, "Parameter Error; visibility\n");
  if (get_error(blue_design_layer_parameter_elements_xml))
    fprintf(stderr, "Parameter Error; elements-xml\n");
}

unsigned char blue_design_layer_get_change(blue_design_layer_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_layer_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_layer_set_change(blue_design_layer_parameter_t p)
{
  changed[p - blue_design_layer_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_layer_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_layer_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_layer_parameter_BEG];
}

static void set_error(blue_design_layer_parameter_t p)
{
  errors[p - blue_design_layer_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

