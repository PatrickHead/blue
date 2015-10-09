/*!
    @file blue-vertices-parms.h

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

    @file blue-vertices-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_VERTICES_PARMS_H
#define BLUE_VERTICES_PARMS_H

#include "vertices.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_vertices_parameter_BEG = 2000,
  blue_vertices_parameter_vertex_xml,
  blue_vertices_parameter_END
} blue_vertices_parameter_t;

vertices_s *blue_vertices_parameter_handler(int argc,
                                            char** argv,
                                            vertices_s *vs);
int blue_vertices_check(vertices_s *vs);
void blue_vertices_check_error(void);
unsigned char blue_vertices_get_change(blue_vertices_parameter_t p);
void blue_vertices_set_change(blue_vertices_parameter_t p);
void blue_vertices_unset_changes(void);

#endif // BLUE_VERTICES_PARMS_H
