/*!
    @file design-line-styles.h

    @brief HEADER_BRIEF

    @timestamp Tue, 11 Nov 2014 07:22:33 +0000

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

    @file design-line-styles.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_LINE_STYLES_H
#define DESIGN_LINE_STYLES_H

#include "list.h"
#include "design-line-style.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  list_s *line_styles;
} design_line_styles_s;

design_line_styles_s *design_line_styles_create(void);
void design_line_styles_destroy(design_line_styles_s *lss);
design_line_styles_s *design_line_styles_copy(design_line_styles_s *lss);
void design_line_styles_add_line_style(design_line_styles_s *lss,
                                       design_line_style_s *ls);
void design_line_styles_delete_line_style(design_line_styles_s *lss, char *name);
design_line_style_s *design_line_styles_get_line_style(design_line_styles_s *lss,
                                                       char *name);

#endif // DESIGN_LINE_STYLES_H
