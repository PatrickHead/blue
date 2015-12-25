/*!
    @file design-line-style-segments.h

    @brief HEADER_BRIEF

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

    @file design-line-style-segments.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_LINE_STYLE_SEGMENTS_H
#define DESIGN_LINE_STYLE_SEGMENTS_H

#include "list.h"
#include "design-line-style-segment.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  list_s *line_style_segments;
} design_line_style_segments_s;

design_line_style_segments_s *design_line_style_segments_create(void);
void design_line_style_segments_destroy(design_line_style_segments_s *lsss);
design_line_style_segments_s *design_line_style_segments_copy(
  design_line_style_segments_s *lsss);
void design_line_style_segments_add_line_style_segment(
  design_line_style_segments_s *lsss,
  design_line_style_segment_s *lss);

#endif // DESIGN_LINE_STYLE_SEGMENTS_H
