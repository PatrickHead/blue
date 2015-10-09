/*!
    @file blue-paper-parms.h

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

    @file blue-paper-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_PAPER_PARMS_H
#define BLUE_PAPER_PARMS_H

#include "paper.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_paper_parameter_BEG = 1000,
  blue_paper_parameter_units = blue_paper_parameter_BEG,
  blue_paper_parameter_size,
  blue_paper_parameter_orientation,
  blue_paper_parameter_margins_xml,
  blue_paper_parameter_width,
  blue_paper_parameter_height,
  blue_paper_parameter_color_xml,
  blue_paper_parameter_END
} blue_paper_parameter_t;

paper_s *blue_paper_parameter_handler(int argc, char** argv, paper_s *p);
int blue_paper_check(paper_s *p);
void blue_paper_check_error(void);
unsigned char blue_paper_get_change(blue_paper_parameter_t p);
void blue_paper_set_change(blue_paper_parameter_t p);
void blue_paper_unset_changes(void);

#endif // BLUE_PAPER_PARMS_H
