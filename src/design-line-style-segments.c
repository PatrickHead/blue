/*!
    @file design-line-style-segments.c

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

    @file design-line-style-segments.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-line-style-segments.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_segments_s *design_line_style_segments_create(void)
{
  design_line_style_segments_s *lsss;

  lsss =
    (design_line_style_segments_s *)malloc(sizeof(design_line_style_segments_s));
  memset(lsss, 0, sizeof(design_line_style_segments_s));

  lsss->line_style_segments = list_create();
  list_set_free(lsss->line_style_segments,
                design_line_style_segment_destroy_void);

    // Return RETVAL
  return lsss;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_segments_destroy(design_line_style_segments_s *lss)
{
    // Sanity check parameters.
  assert(lss);
  if (lss->line_style_segments) list_destroy(lss->line_style_segments);
  free(lss);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_segments_s *design_line_style_segments_copy(
  design_line_style_segments_s *lsss)
{
  design_line_style_segments_s *nlsss;
  design_line_style_segment_s *lss;
  design_line_style_segment_s *nlss;

    // Sanity check parameters.
  assert(lsss);

  nlsss = design_line_style_segments_create();
  memcpy(nlsss, lsss, sizeof(design_line_style_segments_s));

  if (lsss->line_style_segments)
  {
    nlsss->line_style_segments = list_create();
    for (lss =
          (design_line_style_segment_s *)list_head(lsss->line_style_segments);
         lss;
         lss =
          (design_line_style_segment_s *)list_next(lsss->line_style_segments))
    {
      nlss = design_line_style_segment_copy(lss);
      list_insert(nlsss->line_style_segments, (void *)nlss, (void *)TAIL);
    }
  }

    // Return RETVAL
  return nlsss;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_segments_add_line_style_segment(
  design_line_style_segments_s *lsss,
  design_line_style_segment_s *lss)
{
    // Sanity check parameters.
  assert(lsss);
  assert(lss);
  list_insert(lsss->line_style_segments, lss, (void *)TAIL);
}

