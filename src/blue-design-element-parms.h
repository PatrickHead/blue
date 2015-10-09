/*!
    @file blue-design-element-parms.h

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

    @file blue-design-element-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_DESIGN_ELEMENT_PARMS_H
#define BLUE_DESIGN_ELEMENT_PARMS_H

#include "design-element.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_design_element_parameter_BEG = 2000,
  blue_design_element_parameter_id,
  blue_design_element_parameter_units,
  blue_design_element_parameter_line_weight,
  blue_design_element_parameter_line_style,
  blue_design_element_parameter_fill_style,
  blue_design_element_parameter_color_xml,
  blue_design_element_parameter_dimension_xml,
  blue_design_element_parameter_elliptic_xml,
  blue_design_element_parameter_fill_xml,
  blue_design_element_parameter_line_xml,
  blue_design_element_parameter_point_xml,
  blue_design_element_parameter_polyline_xml,
  blue_design_element_parameter_spline_xml,
  blue_design_element_parameter_text_xml,
  blue_design_element_parameter_tolerance_xml,
  blue_design_element_parameter_defaults_xml,
  blue_design_element_parameter_END
} blue_design_element_parameter_t;

design_element_s *blue_design_element_parameter_handler(int argc,
                                                        char** argv,
                                                        design_element_s *e);
int blue_design_element_check(design_element_s *e);
void blue_design_element_check_error(void);
unsigned char blue_design_element_get_change(blue_design_element_parameter_t p);
void blue_design_element_set_change(blue_design_element_parameter_t p);
void blue_design_element_unset_changes(void);

#endif // BLUE_DESIGN_ELEMENT_PARMS_H
