/*!
    @file design-radial-type.h

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

    @file design-radial-type.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_RADIAL_TYPE_H
#define DESIGN_RADIAL_TYPE_H

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef enum
{
  design_radial_type_radius,
  design_radial_type_diameter
} design_radial_t;

design_radial_t str2design_radial_type(char* s);
const char* design_radial_type2str(design_radial_t t);

#endif // DESIGN_RADIAL_TYPE_H
