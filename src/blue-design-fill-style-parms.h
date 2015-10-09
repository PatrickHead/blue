/*!
    @file blue-design-fill-style-parms.h

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

    @file blue-design-fill-style-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_DESIGN_FILL_STYLE_PARMS_H
#define BLUE_DESIGN_FILL_STYLE_PARMS_H

#include "design-fill-style.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_design_fill_style_parameter_BEG = 2000,
  blue_design_fill_style_parameter_name,
  blue_design_fill_style_parameter_TYPE,
  blue_design_fill_style_parameter_line_weight,
  blue_design_fill_style_parameter_line_style,
  blue_design_fill_style_parameter_background_color_xml,
  blue_design_fill_style_parameter_pattern_color_xml,
  blue_design_fill_style_parameter_angle1,
  blue_design_fill_style_parameter_spacing1,
  blue_design_fill_style_parameter_angle2,
  blue_design_fill_style_parameter_spacing2,
  blue_design_fill_style_parameter_source,
  blue_design_fill_style_parameter_END
} blue_design_fill_style_parameter_t;

design_fill_style_s *blue_design_fill_style_parameter_handler(int argc,
                                                              char** argv,
                                                         design_fill_style_s *fs);
int blue_design_fill_style_check(design_fill_style_s *fs);
void blue_design_fill_style_check_error(void);
unsigned char blue_design_fill_style_get_change(
  blue_design_fill_style_parameter_t p);
void blue_design_fill_style_set_change(blue_design_fill_style_parameter_t p);
void blue_design_fill_style_unset_changes(void);

#endif // BLUE_DESIGN_FILL_STYLE_PARMS_H
