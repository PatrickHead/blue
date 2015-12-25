/*!
    @file blue-drawing-parms.h

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

    @file blue-drawing-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_DRAWING_PARMS_H
#define BLUE_DRAWING_PARMS_H

#include "drawing.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_drawing_parameter_BEG = 2000,
  blue_drawing_parameter_paper_xml,
  blue_drawing_parameter_border_xml,
  blue_drawing_parameter_title_block_xml,
  blue_drawing_parameter_design_xml,
  blue_drawing_parameter_END
} blue_drawing_parameter_t;

drawing_s *blue_drawing_parameter_handler(int argc, char** argv, drawing_s *d);
int blue_drawing_check(drawing_s *d);
void blue_drawing_check_error(void);
unsigned char blue_drawing_get_change(blue_drawing_parameter_t p);
void blue_drawing_set_change(blue_drawing_parameter_t p);
void blue_drawing_unset_changes(void);

#endif // BLUE_DRAWING_PARMS_H
