/*!
    @file design-fill-styles.h

    @brief Header file for design fill styles list data

    @timestamp Fri, 28 Nov 2014 18:21:07 +0000

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

    @brief Header file for design fill styles list data

    Structure and functions for maintaining a list of design fill styles.

  */

#ifndef DESIGN_FILL_STYLES_H
#define DESIGN_FILL_STYLES_H

  // External include files

#include "list.h"

  // Project specific include files

#include "design-fill-style.h"

  /*!
    @brief Design fill style list structure
  */

typedef struct
{
    /*! @brief List of design fill styles */
  list_s *fill_styles;
} design_fill_styles_s;

  // Structure maintenance functions

design_fill_styles_s *design_fill_styles_create(void);
void design_fill_styles_destroy(design_fill_styles_s *fss);
design_fill_styles_s *design_fill_styles_copy(design_fill_styles_s *fss);

  // List management functions

void design_fill_styles_add_fill_style(design_fill_styles_s *fss,
                                       design_fill_style_s *fs);
void design_fill_styles_delete_fill_style(design_fill_styles_s *fss, char *name);
design_fill_style_s *design_fill_styles_get_fill_style(design_fill_styles_s *fss,
                                                       char *name);

#endif // DESIGN_FILL_STYLES_H
