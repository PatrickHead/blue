/*!
    @file blue-design-defaults-parms.h

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

    @file blue-design-defaults-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_DESIGN_DEFAULTS_PARMS_H
#define BLUE_DESIGN_DEFAULTS_PARMS_H

#include "design-defaults.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_design_defaults_parameter_BEG = 2000,
  blue_design_defaults_parameter_units,
  blue_design_defaults_parameter_line_weight,
  blue_design_defaults_parameter_line_style,
  blue_design_defaults_parameter_fill_style,
  blue_design_defaults_parameter_dimension_text_size,
  blue_design_defaults_parameter_dimension_precision,
  blue_design_defaults_parameter_angular_gap,
  blue_design_defaults_parameter_angular_extension,
  blue_design_defaults_parameter_linear_gap,
  blue_design_defaults_parameter_linear_extension_above,
  blue_design_defaults_parameter_linear_extension_below,
  blue_design_defaults_parameter_tolerance_text_size,
  blue_design_defaults_parameter_tolerance_plus,
  blue_design_defaults_parameter_tolerance_minus,
  blue_design_defaults_parameter_tolerance_precision,
  blue_design_defaults_parameter_background_color_xml,
  blue_design_defaults_parameter_element_color_xml,
  blue_design_defaults_parameter_END
} blue_design_defaults_parameter_t;

design_defaults_s *blue_design_defaults_parameter_handler(int argc,
                                                          char** argv,
                                                          design_defaults_s *d);
int blue_design_defaults_check(design_defaults_s *d);
void blue_design_defaults_check_error(void);
unsigned char blue_design_defaults_get_change(
  blue_design_defaults_parameter_t p);
void blue_design_defaults_set_change(blue_design_defaults_parameter_t p);
void blue_design_defaults_unset_changes(void);

#endif // BLUE_DESIGN_DEFAULTS_PARMS_H
