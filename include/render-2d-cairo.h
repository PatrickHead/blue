/*!
    @file render-2d-cairo.h

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

    @file render-2d-cairo.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef RENDER2_H
#define RENDER2_H

#include <cairo.h>

#include "drawing.h"

cairo_surface_t *render_2d_cairo(drawing_s *d);
void get_surface_size(cairo_surface_t *surface, cairo_rectangle_t *rect);

#endif // RENDER2_H
