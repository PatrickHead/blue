/*!
    @file design-polyline.h

    @brief HEADER_BRIEF

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

    @file design-polyline.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_POLYLINE_H
#define DESIGN_POLYLINE_H

#include "vertices.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  vertices_s *vertices;
} design_polyline_s;

design_polyline_s *design_polyline_create(void);
void design_polyline_destroy(design_polyline_s *pl);
design_polyline_s *design_polyline_copy(design_polyline_s *el);

void design_polyline_set(design_polyline_s *pl, vertices_s *vertices);
void design_polyline_get(design_polyline_s *pl, vertices_s **vertices);

void design_polyline_set_vertices(design_polyline_s *pl, vertices_s *vertices);
vertices_s *design_polyline_get_vertices(design_polyline_s *pl);

#endif // DESIGN_POLYLINE_H
