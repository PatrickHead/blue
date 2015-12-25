/*!
    @file design-visibility-type.h

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

    @file design-visibility-type.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_VISIBILITY_TYPE_H
#define DESIGN_VISIBILITY_TYPE_H

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef enum
{
  design_visibility_type_visible = 0,
  design_visibility_type_hidden
} design_visibility_t;

design_visibility_t str2design_visibility_type(char* s);
const char* design_visibility_type2str(design_visibility_t t);

#endif // DESIGN_VISIBILITY_TYPE_H
