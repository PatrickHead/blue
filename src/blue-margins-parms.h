/*!
    @file blue-margins-parms.h

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

    @file blue-margins-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_MARGINS_PARMS_H
#define BLUE_MARGINS_PARMS_H

#include "margins.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_margins_parameter_BEG = 2000,
  blue_margins_parameter_units = blue_margins_parameter_BEG,
  blue_margins_parameter_top,
  blue_margins_parameter_bottom,
  blue_margins_parameter_left,
  blue_margins_parameter_right,
  blue_margins_parameter_END
} blue_margins_parameter_t;

margins_s *blue_margins_parameter_handler(int argc, char** argv, margins_s *m);
int blue_margins_check(margins_s *m);
void blue_margins_check_error(void);
unsigned char blue_margins_get_change(blue_margins_parameter_t p);
void blue_margins_set_change(blue_margins_parameter_t p);
void blue_margins_unset_changes(void);

#endif // BLUE_MARGINS_PARMS_H
