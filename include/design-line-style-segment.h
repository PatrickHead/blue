/*!
    @file design-line-style-segment.h

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

    @file design-line-style-segment.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_LINE_STYLE_SEGMENT_H
#define DESIGN_LINE_STYLE_SEGMENT_H

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  double length;
} design_line_style_segment_s;

design_line_style_segment_s *design_line_style_segment_create(void);
void design_line_style_segment_destroy_void(void *v);
void design_line_style_segment_destroy(design_line_style_segment_s *lss);
design_line_style_segment_s *design_line_style_segment_copy(
  design_line_style_segment_s *lss);

void design_line_style_segment_set(design_line_style_segment_s *lss,
                      double length);
void design_line_style_segment_get(design_line_style_segment_s *lss,
                      double *length);

void design_line_style_segment_set_length(design_line_style_segment_s *lss,
                                          double length); 
double design_line_style_segment_get_length(design_line_style_segment_s *lss);

#endif // DESIGN_LINE_STYLE_SEGMENT_H
