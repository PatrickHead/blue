/*!
    @file design-spline.h

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

    @file design-spline.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_SPLINE_H
#define DESIGN_SPLINE_H

#include "vertices.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  vertices_s *vertices;
} design_spline_s;

design_spline_s *design_spline_create(void);
void design_spline_destroy(design_spline_s *s);
design_spline_s *design_spline_copy(design_spline_s *s);

void design_spline_set(design_spline_s *s, vertices_s *vertices);
void design_spline_get(design_spline_s *s, vertices_s **vertices);

void design_spline_set_vertices(design_spline_s *s, vertices_s *vertices);
vertices_s *design_spline_get_vertices(design_spline_s *s);

#endif // DESIGN_SPLINE_H
