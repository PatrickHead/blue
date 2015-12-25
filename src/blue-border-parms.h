/*!
    @file blue-border-parms.h

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

    @file blue-border-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_BORDER_PARMS_H
#define BLUE_BORDER_PARMS_H

#include "border.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_border_parameter_BEG = 2000,
  blue_border_parameter_units = blue_border_parameter_BEG,
  blue_border_parameter_line_width,
  blue_border_parameter_background_color_xml,
  blue_border_parameter_line_color_xml,
  blue_border_parameter_margins_xml,
  blue_border_parameter_END
} blue_border_parameter_t;

border_s *blue_border_parameter_handler(int argc, char** argv, border_s *b);
int blue_border_check(border_s *b);
void blue_border_check_error(void);
unsigned char blue_border_get_change(blue_border_parameter_t p);
void blue_border_set_change(blue_border_parameter_t p);
void blue_border_unset_changes(void);

#endif // BLUE_BORDER_PARMS_H
