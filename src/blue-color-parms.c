/*!
    @file blue-color-parms.c

    @brief SOURCE_BRIEF

    @timestamp Mon, 06 Jan 2014 15:17:36 +0000

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

    @file blue-color-parms.c

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

#include "blue-color-parms.h"

static unsigned char errors[blue_color_parameter_END - blue_color_parameter_BEG];
static unsigned char changed[blue_color_parameter_END - blue_color_parameter_BEG];

static unsigned char get_error(blue_color_parameter_t p);
static void set_error(blue_color_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

color_s *blue_color_parameter_handler(int argc, char** argv, color_s *color)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "tag", 1, 0, blue_color_parameter_tag },
      { "r", 1, 0, blue_color_parameter_r },
      { "g", 1, 0, blue_color_parameter_g },
      { "b", 1, 0, blue_color_parameter_b },
      { "a", 1, 0, blue_color_parameter_a },
      { 0, 0, 0, 0 }
    };

  if (!color) color = color_create();
  if (!color) return NULL;

  blue_color_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_color_parameter_tag:
        color->tag = strdup(optarg);
        blue_color_set_change(blue_color_parameter_tag);
        break;
      case blue_color_parameter_r:
        color->r = strtod(optarg, NULL);
        blue_color_set_change(blue_color_parameter_r);
        break;
      case blue_color_parameter_g:
        color->g = strtod(optarg, NULL);
        blue_color_set_change(blue_color_parameter_g);
        break;
      case blue_color_parameter_b:
        color->b = strtod(optarg, NULL);
        blue_color_set_change(blue_color_parameter_b);
        break;
      case blue_color_parameter_a:
        color->a = strtod(optarg, NULL);
        blue_color_set_change(blue_color_parameter_a);
        break;
    }
  }

  blue_color_unset_changes();

    // Return RETVAL
  return color;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_color_check(color_s *color)
{
  int i;

    // Sanity check parameters.
  assert(color);

  unset_errors();

  if ((color->r < 0.0) || (color->r > 255.0)) set_error(blue_color_parameter_r);
  if ((color->g < 0.0) || (color->g > 255.0)) set_error(blue_color_parameter_g);
  if ((color->b < 0.0) || (color->b > 255.0)) set_error(blue_color_parameter_b);
  if ((color->a < 0.0) || (color->a > 255.0)) set_error(blue_color_parameter_a);

  for (i = blue_color_parameter_BEG; i < blue_color_parameter_END; i++)
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

void blue_color_check_error(void)
{
  if (get_error(blue_color_parameter_tag))
    fprintf(stderr, "Parameter Error; tag\n");
  if (get_error(blue_color_parameter_r))
    fprintf(stderr, "Parameter Error; r\n");
  if (get_error(blue_color_parameter_g))
    fprintf(stderr, "Parameter Error; g\n");
  if (get_error(blue_color_parameter_b))
    fprintf(stderr, "Parameter Error; b\n");
  if (get_error(blue_color_parameter_a))
    fprintf(stderr, "Parameter Error; a\n");
}

unsigned char blue_color_get_change(blue_color_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_color_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_color_set_change(blue_color_parameter_t p)
{
  changed[p - blue_color_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_color_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_color_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_color_parameter_BEG];
}

static void set_error(blue_color_parameter_t p)
{
  errors[p - blue_color_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

