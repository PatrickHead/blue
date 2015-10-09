/*!
    @file design-point.h

    @brief HEADER_BRIEF

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

    @file design-point.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_POINT_H
#define DESIGN_POINT_H

#include "vertex.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  vertex_s *location;
} design_point_s;

design_point_s *design_point_create(void);
void design_point_destroy(design_point_s *p);
design_point_s *design_point_copy(design_point_s *p);

void design_point_set(design_point_s *p,
                      vertex_s *location);
void design_point_get(design_point_s *p,
                      vertex_s **location);

void design_point_set_location(design_point_s *p, vertex_s *location); 
vertex_s *design_point_get_location(design_point_s *p);

#endif // DESIGN_POINT_H
