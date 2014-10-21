/*!
    @file border.h

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

    @file border.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BORDER_H
#define BORDER_H

#include "units.h"
#include "margins.h"
#include "color.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! brief ELEMENT_BRIEF */
  units_t units;
    /*! brief ELEMENT_BRIEF */
  double line_width;
    /*! brief ELEMENT_BRIEF */
  margins_s *margins;
    /*! brief ELEMENT_BRIEF */
  color_s *background_color;
    /*! brief ELEMENT_BRIEF */
  color_s *line_color;
} border_s;

border_s *border_create(void);
void border_destroy(border_s *b);
border_s *border_copy(border_s *b);

void border_set(border_s *b,
                units_t units,
                double line_width,
                margins_s *margins,
                color_s *background_color,
                color_s *line_color);
void border_get(border_s *b,
                units_t *units,
                double *line_width,
                margins_s **margins,
                color_s **background_color,
                color_s **line_color);

void border_set_units(border_s *b, units_t ut);
units_t border_get_units(border_s *b);

void border_set_line_width(border_s *b, double lw);
double border_get_line_width(border_s *b);

void border_set_margins(border_s *b, margins_s *m);
margins_s *border_get_margins(border_s *b);

void border_set_background_color(border_s *b, color_s *background_color);
color_s *border_get_background_color(border_s *b);

void border_set_line_color(border_s *b, color_s *line_color);
color_s *border_get_line_color(border_s *b);

#endif // BORDER_H

