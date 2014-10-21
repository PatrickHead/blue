/*!
    @file design-fill-styles.h

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

    @file design-fill-styles.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_FILL_STYLES_H
#define DESIGN_FILL_STYLES_H

#include "list.h"
#include "design-fill-style.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! brief ELEMENT_BRIEF */
  list_s *fill_styles;
} design_fill_styles_s;

design_fill_styles_s *design_fill_styles_create(void);
void design_fill_styles_destroy(design_fill_styles_s *fss);
design_fill_styles_s *design_fill_styles_copy(design_fill_styles_s *fss);
void design_fill_styles_add_fill_style(design_fill_styles_s *fss,
                                       design_fill_style_s *fs);
void design_fill_styles_delete_fill_style(design_fill_styles_s *fss, char *name);
design_fill_style_s *design_fill_styles_get_fill_style(design_fill_styles_s *fss,
                                                       char *name);

#endif // DESIGN_FILL_STYLES_H
