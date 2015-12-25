/*!
    @file blue-vertices-parms.c

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

    @file blue-vertices-parms.c

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

#include "units.h"
#include "vertices-xml.h"

#include "blue-vertices-parms.h"

static unsigned char errors[blue_vertices_parameter_END
                            - blue_vertices_parameter_BEG];
static unsigned char changed[blue_vertices_parameter_END
                             - blue_vertices_parameter_BEG];

static unsigned char get_error(blue_vertices_parameter_t p);
static void set_error(blue_vertices_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertices_s *blue_vertices_parameter_handler(int argc,
                                            char** argv,
                                            vertices_s *vs)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "vertex-xml", 1, 0, blue_vertices_parameter_vertex_xml },
      { 0, 0, 0, 0 }
    };
  vertex_s *v;
  xmlDocPtr doc;

  if (!vs) vs = vertices_create();
  if (!vs) return NULL;

  blue_vertices_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_vertices_parameter_vertex_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        v = vertex_from_xml_doc(doc);
        vertices_add_vertex(vs, v);
        xmlFreeDoc(doc);
        blue_vertices_set_change(blue_vertices_parameter_vertex_xml);
        break;
      default: break;
    }
  }

  blue_vertices_unset_changes();

    // Return RETVAL
  return vs;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_vertices_check(vertices_s *vs)
{
  int i;

    // Sanity check parameters.
  assert(vs);

  unset_errors();

  for (i = blue_vertices_parameter_BEG;
       i < blue_vertices_parameter_END;
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

void blue_vertices_check_error(void)
{
  if (get_error(blue_vertices_parameter_vertex_xml))
    fprintf(stderr, "Parameter Error; vertex-xml\n");
}

unsigned char blue_vertices_get_change(blue_vertices_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_vertices_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_vertices_set_change(blue_vertices_parameter_t p)
{
  changed[p - blue_vertices_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_vertices_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_vertices_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_vertices_parameter_BEG];
}

static void set_error(blue_vertices_parameter_t p)
{
  errors[p - blue_vertices_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

