/*!
    @file blue-color-parms.h

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

    @file blue-color-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_COLOR_PARMS_H
#define BLUE_COLOR_PARMS_H

#include "color.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_color_parameter_BEG = 2000,
  blue_color_parameter_tag,
  blue_color_parameter_r,
  blue_color_parameter_g,
  blue_color_parameter_b,
  blue_color_parameter_a,
  blue_color_parameter_END
} blue_color_parameter_t;

color_s *blue_color_parameter_handler(int argc, char** argv, color_s *color);
int blue_color_check(color_s *color);
void blue_color_check_error(void);
unsigned char blue_color_get_change(blue_color_parameter_t p);
void blue_color_set_change(blue_color_parameter_t p);
void blue_color_unset_changes(void);

#endif // BLUE_COLOR_PARMS_H
