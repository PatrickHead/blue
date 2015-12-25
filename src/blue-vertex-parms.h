/*!
    @file blue-vertex-parms.h

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

    @file blue-vertex-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_VERTEX_PARMS_H
#define BLUE_VERTEX_PARMS_H

#include "vertex.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_vertex_parameter_BEG = 2000,
  blue_vertex_parameter_tag,
  blue_vertex_parameter_x,
  blue_vertex_parameter_y,
  blue_vertex_parameter_z,
  blue_vertex_parameter_END
} blue_vertex_parameter_t;

vertex_s *blue_vertex_parameter_handler(int argc, char** argv, vertex_s *v);
int blue_vertex_check(vertex_s *v);
void blue_vertex_check_error(void);
unsigned char blue_vertex_get_change(blue_vertex_parameter_t p);
void blue_vertex_set_change(blue_vertex_parameter_t p);
void blue_vertex_unset_changes(void);

#endif // BLUE_VERTEX_PARMS_H
