/*!
    @file blue-title-block-parms.h

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

    @file blue-title-block-parms.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BLUE_TITLE_BLOCK_PARMS_H
#define BLUE_TITLE_BLOCK_PARMS_H

#include "title-block.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef enum
{
  blue_title_block_parameter_BEG = 2000,
  blue_title_block_parameter_title = blue_title_block_parameter_BEG,
  blue_title_block_parameter_part,
  blue_title_block_parameter_provider,
  blue_title_block_parameter_consumer,
  blue_title_block_parameter_revision,
  blue_title_block_parameter_reference,
  blue_title_block_parameter_page,
  blue_title_block_parameter_of,
  blue_title_block_parameter_time,
  blue_title_block_parameter_background_color_xml,
  blue_title_block_parameter_line_color_xml,
  blue_title_block_parameter_text_color_xml,
  blue_title_block_parameter_END
} blue_title_block_parameter_t;

title_block_s *blue_title_block_parameter_handler(int argc,
                                                  char** argv,
                                                  title_block_s *tb);
int blue_title_block_check(title_block_s *tb);
void blue_title_block_check_error(void);
unsigned char blue_title_block_get_change(blue_title_block_parameter_t p);
void blue_title_block_set_change(blue_title_block_parameter_t p);
void blue_title_block_unset_changes(void);

#endif // BLUE_TITLE_BLOCK_PARMS_H
