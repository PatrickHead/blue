/*!
    @file design-dimension-type.h

    @brief Header file for design dimension type definitions

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

    @file design-dimension-type.h

    @brief Header file for design dimension type definitions

    Type definitions for design dimension elements.

  */

#ifndef DESIGN_DIMENSION_TYPE_H
#define DESIGN_DIMENSION_TYPE_H

  /*!
    @brief Design dimension types
  */

typedef enum
{
  design_dimension_type_BEG = 0,
  design_dimension_type_linear = 0,
  design_dimension_type_angular,
  design_dimension_type_radial,
  design_dimension_type_END,
} design_dimension_t;

  // Utility functions for converting to/from strings

design_dimension_t str2design_dimension_type(char* s);
const char* design_dimension_type2str(design_dimension_t t);

#endif // DESIGN_DIMENSION_TYPE_H
