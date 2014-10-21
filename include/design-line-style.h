/*!
    @file design-line-style.h

    @brief HEADER_BRIEF

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

    @file design-line-style.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_LINE_STYLE_H
#define DESIGN_LINE_STYLE_H

#include "list.h"

#include "design-line-style-segments.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! brief ELEMENT_BRIEF */
  char *name;
    /*! brief ELEMENT_BRIEF */
  design_line_style_segments_s *line_style_segments;
} design_line_style_s;

design_line_style_s *design_line_style_create(void);
void design_line_style_destroy_void(void *v);
void design_line_style_destroy(design_line_style_s *dls);
design_line_style_s *design_line_style_copy(design_line_style_s *dls);

void design_line_style_set(design_line_style_s *dls,
                           char *name,
                           design_line_style_segments_s *line_style_segments);
void design_line_style_get(design_line_style_s *dls,
                           char **name,
                           design_line_style_segments_s **line_style_segments);

void design_line_style_set_name(design_line_style_s *dls, char *name);
char *design_line_style_get_name(design_line_style_s *dls);

void design_line_style_set_line_style_segments(design_line_style_s *dls,
                                              design_line_style_segments_s *lsss);
design_line_style_segments_s *design_line_style_get_line_style_segments(
  design_line_style_s *dls);

void design_line_style_add_segment(design_line_style_s *dls,
                                   design_line_style_segment_s *lss);

#endif // DESIGN_LINE_STYLE_H
