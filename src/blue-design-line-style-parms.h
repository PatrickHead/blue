/*!
    @file blue-design-line-style-parms.h

    @brief HEADER_BRIEF

    @timestamp Mon, 06 Jan 2014 15:17:36 +0000

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

    @file blue-design-line-style-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_DESIGN_LINE_STYLE_PARMS_H
#define BLUE_DESIGN_LINE_STYLE_PARMS_H

#include "design-line-style.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_design_line_style_parameter_BEG = 2000,
  blue_design_line_style_parameter_name,
  blue_design_line_style_parameter_segments_xml,
  blue_design_line_style_parameter_END
} blue_design_line_style_parameter_t;

design_line_style_s *blue_design_line_style_parameter_handler(int argc,
                                                              char** argv,
                                                         design_line_style_s *ls);
int blue_design_line_style_check(design_line_style_s *ls);
void blue_design_line_style_check_error(void);
unsigned char blue_design_line_style_get_change(
  blue_design_line_style_parameter_t p);
void blue_design_line_style_set_change(
  blue_design_line_style_parameter_t p);
void blue_design_line_style_unset_changes(void);

#endif // BLUE_DESIGN_LINE_STYLE_PARMS_H
