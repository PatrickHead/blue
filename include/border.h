/*!
    @file border.h

    @brief Header file for paper border data

    @timestamp Fri, 28 Nov 2014 17:41:13 +0000

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

    @brief Header file for paper border structure and maintenance functions.

    A paper border definition contains the properties needed to control the
    rendering of a border area on a sheet of paper, such as margins, colors,
    etc.

  */

#ifndef BORDER_H
#define BORDER_H

  // External include files

#include "color.h"

  // Project specific include files

#include "units.h"
#include "margins.h"

  /*!
    @brief Paper border structure type
  */

typedef struct
{
    /*! @brief Unit of measure (ie. mm, or inch) */
  units_t units;
    /*! @brief Width of border outlines, if any */
  double line_width;
    /*! @brief Sub-structure containing dimensions of all four margins */
  margins_s *margins;
    /*! @brief Background color (by name) */
  color_s *background_color;
    /*! @brief Color of outlines */
  color_s *line_color;
} border_s;

  // Border function prototypes

    // Structure management functions

border_s *border_create(void);
void border_destroy(border_s *b);
border_s *border_copy(border_s *b);

    // Comprehensive getter/setter

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

    // Individual element getters/setters

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

