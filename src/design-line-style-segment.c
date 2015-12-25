/*!
    @file design-line-style-segment.c

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

    @file design-line-style-segment.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-line-style-segment.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_segment_s *design_line_style_segment_create(void)
{
  design_line_style_segment_s *line_style_segment;

  line_style_segment =
    (design_line_style_segment_s *)malloc(sizeof(design_line_style_segment_s));
  memset(line_style_segment, 0, sizeof(design_line_style_segment_s));

    // Return RETVAL
  return line_style_segment;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_segment_destroy_void(void *v)
{
    // Sanity check parameters.
  assert(v);
  design_line_style_segment_destroy((design_line_style_segment_s *)v);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_segment_destroy(design_line_style_segment_s *lss)
{
    // Sanity check parameters.
  assert(lss);
  free(lss);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_segment_s *design_line_style_segment_copy(
  design_line_style_segment_s *lss)
{
  design_line_style_segment_s *nlss;

    // Sanity check parameters.
  assert(lss);

  nlss = design_line_style_segment_create();
  memcpy(nlss, lss, sizeof(design_line_style_segment_s));

    // Return RETVAL
  return nlss;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_segment_set(design_line_style_segment_s *lss,
                      double length)
{
    // Sanity check parameters.
  assert(lss);

  design_line_style_segment_set_length(lss, length);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_segment_get(design_line_style_segment_s *lss,
                      double *length)
{
    // Sanity check parameters.
  assert(lss);
  assert(length);

  *length = design_line_style_segment_get_length(lss);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_segment_set_length(design_line_style_segment_s *lss,
                                          double length)
{
    // Sanity check parameters.
  assert(lss);
  lss->length = length;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_line_style_segment_get_length(design_line_style_segment_s *lss)
{
    // Sanity check parameters.
  assert(lss);
    // Return RETVAL
  return lss->length;
}

