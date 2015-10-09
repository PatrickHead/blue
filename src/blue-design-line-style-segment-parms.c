/*!
    @file blue-design-line-style-segment-parms.c

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

    @file blue-design-line-style-segment-parms.c

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

#include "blue-design-line-style-segment-parms.h"

static unsigned char errors[blue_design_line_style_segment_parameter_END
                            - blue_design_line_style_segment_parameter_BEG];
static unsigned char changed[blue_design_line_style_segment_parameter_END
                             - blue_design_line_style_segment_parameter_BEG];

static unsigned char get_error(blue_design_line_style_segment_parameter_t p);
static void set_error(blue_design_line_style_segment_parameter_t p);
static void unset_errors(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_segment_s *blue_design_line_style_segment_parameter_handler(
  int argc, char** argv, design_line_style_segment_s *lss)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "length", 1, 0, blue_design_line_style_segment_parameter_length },
      { 0, 0, 0, 0 }
    };

  if (!lss) lss = design_line_style_segment_create();
  if (!lss) return NULL;

  blue_design_line_style_segment_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_line_style_segment_parameter_length:
        design_line_style_segment_set_length(lss, strtod(optarg, NULL));
        blue_design_line_style_segment_set_change(
          blue_design_line_style_segment_parameter_length);
        break;
    }
  }

  blue_design_line_style_segment_unset_changes();

    // Return RETVAL
  return lss;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int blue_design_line_style_segment_check(design_line_style_segment_s *lss)
{
  int i;

    // Sanity check parameters.
  assert(lss);

  unset_errors();

  if (lss->length < 0.0)
    set_error(blue_design_line_style_segment_parameter_length);

  for (i = blue_design_line_style_segment_parameter_BEG;
       i < blue_design_line_style_segment_parameter_END;
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

void blue_design_line_style_segment_check_error(void)
{
  if (get_error(blue_design_line_style_segment_parameter_length))
    fprintf(stderr, "Parameter Error; length\n");
}

unsigned char blue_design_line_style_segment_get_change(
  blue_design_line_style_segment_parameter_t p)
{
    // Return RETVAL
  return changed[p - blue_design_line_style_segment_parameter_BEG];
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_line_style_segment_set_change(
  blue_design_line_style_segment_parameter_t p)
{
  changed[p - blue_design_line_style_segment_parameter_BEG] = 1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void blue_design_line_style_segment_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_line_style_segment_parameter_t p)
{
    // Return RETVAL
  return errors[p - blue_design_line_style_segment_parameter_BEG];
}

static void set_error(blue_design_line_style_segment_parameter_t p)
{
  errors[p - blue_design_line_style_segment_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

