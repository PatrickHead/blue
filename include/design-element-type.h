/*!
    @file design-element-type.h

    @brief Header file for design element type definition

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

    @file design-element-type.h

    @brief Header file for design element type definition

    Defines design element types and utility functions.

  */

#ifndef DESIGN_ELEMENT_TYPE_H
#define DESIGN_ELEMENT_TYPE_H

  /*!
    @brief Design element types
  */

typedef enum
{
  design_element_type_BEG = 0,
  design_element_type_dimension = 0,
  design_element_type_elliptic,
  design_element_type_line,
  design_element_type_point,
  design_element_type_polyline,
  design_element_type_spline,
  design_element_type_text,
  design_element_type_tolerance,
  design_element_type_END
} design_element_t;

  // Utility functions to convert to/from string

design_element_t str2design_element_type(char* s);
const char* design_element_type2str(design_element_t t);

#endif // DESIGN_ELEMENT_TYPE_H
