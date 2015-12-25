/*!
    @file blue-design-elliptic-parms.h

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

    @file blue-design-elliptic-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_DESIGN_ELLIPTIC_PARMS_H
#define BLUE_DESIGN_ELLIPTIC_PARMS_H

#include "design-elliptic.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_design_elliptic_parameter_BEG = 2000,
  blue_design_elliptic_parameter_center = blue_design_elliptic_parameter_BEG,
  blue_design_elliptic_parameter_width,
  blue_design_elliptic_parameter_height,
  blue_design_elliptic_parameter_rotation,
  blue_design_elliptic_parameter_start_angle,
  blue_design_elliptic_parameter_end_angle,
  blue_design_elliptic_parameter_defaults_xml,
  blue_design_elliptic_parameter_END
} blue_design_elliptic_parameter_t;

design_elliptic_s *blue_design_elliptic_parameter_handler(int argc,
                                                          char** argv,
                                                          design_elliptic_s *e);
int blue_design_elliptic_check(design_elliptic_s *e);
void blue_design_elliptic_check_error(void);
unsigned char blue_design_elliptic_get_change(
                blue_design_elliptic_parameter_t p);
void blue_design_elliptic_set_change(blue_design_elliptic_parameter_t p);
void blue_design_elliptic_unset_changes(void);

#endif // BLUE_DESIGN_ELLIPTIC_PARMS_H
