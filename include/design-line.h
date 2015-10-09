/*!
    @file design-line.h

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

    @file design-line.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_VERTEX_H
#define DESIGN_VERTEX_H

#include "vertex.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  vertex_s *start;
    /*! @brief ELEMENT_BRIEF */
  vertex_s *end;
} design_line_s;

design_line_s *design_line_create(void);
void design_line_destroy(design_line_s *l);
design_line_s *design_line_copy(design_line_s *l);

void design_line_set(design_line_s *l,
                     vertex_s *start,
                     vertex_s *end);
void design_line_get(design_line_s *l,
                     vertex_s **start,
                     vertex_s **end);

void design_line_set_start(design_line_s *l, vertex_s *start); 
vertex_s *design_line_get_start(design_line_s *l);
void design_line_set_end(design_line_s *l, vertex_s *end); 
vertex_s *design_line_get_end(design_line_s *l);

#endif // DESIGN_VERTEX_H
