/*!
    @file design-fill-style-type.h

    @brief Header file for design fill style type definitions

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

    @file design-fill-style-type.h

    @brief Header file for design fill style type definitions

    Defines design fill style types and utility functions.

  */

#ifndef DESIGN_FILL_STYLE_TYPE
#define DESIGN_FILL_STYLE_TYPE

  /*!
    @brief Design fill style types
  */

typedef enum
{
  design_fill_style_type_line,
  design_fill_style_type_hatch,
  design_fill_style_type_stipple,
  design_fill_style_type_source_only
} design_fill_style_t;

  // Utility functions to convert to/from string

design_fill_style_t str2design_fill_style_type(char* s);
const char* design_fill_style_type2str(design_fill_style_t t);

#endif // DESIGN_FILL_STYLE_TYPE
