/*!
    @file blue-vertex-parms.c

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

    @file blue-vertex-parms.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

  // Project related headers

#include "blue-vertex-parms.h"

static unsigned char errors[blue_vertex_parameter_END - blue_vertex_parameter_BEG];
static unsigned char changed[blue_vertex_parameter_END - blue_vertex_parameter_BEG];

static unsigned char get_error(blue_vertex_parameter_t p);
static void set_error(blue_vertex_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *blue_vertex_parameter_handler(int argc, char** argv, vertex_s *v)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "tag", 1, 0, blue_vertex_parameter_tag },
      { "x", 1, 0, blue_vertex_parameter_x },
      { "y", 1, 0, blue_vertex_parameter_y },
      { "z", 1, 0, blue_vertex_parameter_z },
      { 0, 0, 0, 0 }
    };

  if (!v) v = vertex_create();
  if (!v) return NULL;

  blue_vertex_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_vertex_parameter_tag:
        v->tag = strdup(optarg);
        blue_vertex_set_change(blue_vertex_parameter_tag);
        break;
      case blue_vertex_parameter_x:
        v->x = strtod(optarg, NULL);
        blue_vertex_set_change(blue_vertex_parameter_x);
        break;
      case blue_vertex_parameter_y:
        v->y = strtod(optarg, NULL);
        blue_vertex_set_change(blue_vertex_parameter_y);
        break;
      case blue_vertex_parameter_z:
        v->z = strtod(optarg, NULL);
        blue_vertex_set_change(blue_vertex_parameter_z);
        break;
    }
  }

  blue_vertex_unset_changes();

    // Return RETVAL
  return v;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_vertex_check(vertex_s *v)
{
  int i;

    // Sanity check parameters.
  assert(v);

  unset_errors();

  for (i = blue_vertex_parameter_BEG; i < blue_vertex_parameter_END; i++)
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

void blue_vertex_check_error(void)
{
  if (get_error(blue_vertex_parameter_tag))
    fprintf(stderr, "Parameter Error; tag\n");
  if (get_error(blue_vertex_parameter_x))
    fprintf(stderr, "Parameter Error; x\n");
  if (get_error(blue_vertex_parameter_y))
    fprintf(stderr, "Parameter Error; x\n");
  if (get_error(blue_vertex_parameter_z))
    fprintf(stderr, "Parameter Error; x\n");
}

unsigned char blue_vertex_get_change(blue_vertex_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_vertex_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_vertex_set_change(blue_vertex_parameter_t p)
{
  changed[p - blue_vertex_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_vertex_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_vertex_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_vertex_parameter_BEG];
}

static void set_error(blue_vertex_parameter_t p)
{
  errors[p - blue_vertex_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

