/*!
    @file design-anchor-location-type.h

    @brief Header file for design anchor location type definition.

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

    @file design-anchor-location-type.h

    @brief Header file for design anchor location type definition.

    Defines possible anchor location positions, such as "upper left".  These
    anchor positions are used to offset text position locations, relative to
    the length and width of the text, and possibly other object types.

  */

#ifndef DESIGN_ANCHOR_LOCATION_TYPE_H
#define DESIGN_ANCHOR_LOCATION_TYPE_H

  /*!
    @brief Anchor location types
  */

typedef enum
{
  design_anchor_location_type_upper_left,
  design_anchor_location_type_upper_right,
  design_anchor_location_type_center,
  design_anchor_location_type_lower_left,
  design_anchor_location_type_lower_right
} design_anchor_location_t;

  // Utility functions for converting types to/from strings

design_anchor_location_t str2design_anchor_location_type(char* s);
const char* design_anchor_location_type2str(design_anchor_location_t t);

#endif // DESIGN_ANCHOR_LOCATION_TYPE_H
