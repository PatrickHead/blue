/*!
    @file blue-design-dimension-parms.h

    @brief HEADER_BRIEF

    @timestamp Tue, 21 Oct 2014 14:39:36 +0000

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

    @file blue-design-dimension-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_DESIGN_DIMENSION_PARMS_H
#define BLUE_DESIGN_DIMENSION_PARMS_H

#include "design-dimension.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_design_dimension_parameter_BEG = 2000,
  blue_design_dimension_parameter_text_size = blue_design_dimension_parameter_BEG,
  blue_design_dimension_parameter_text_location,
  blue_design_dimension_parameter_precision,
  blue_design_dimension_parameter_angular_xml,
  blue_design_dimension_parameter_linear_xml,
  blue_design_dimension_parameter_radial_xml,
  blue_design_dimension_parameter_defaults_xml,
  blue_design_dimension_parameter_END
} blue_design_dimension_parameter_t;

design_dimension_s *blue_design_dimension_parameter_handler(int argc,
                                                            char** argv,
                                                          design_dimension_s *d);
int blue_design_dimension_check(design_dimension_s *d);
void blue_design_dimension_check_error(void);
unsigned char blue_design_dimension_get_change(
                blue_design_dimension_parameter_t p);
void blue_design_dimension_set_change(blue_design_dimension_parameter_t p);
void blue_design_dimension_unset_changes(void);

#endif // BLUE_DESIGN_DIMENSION_PARMS_H
