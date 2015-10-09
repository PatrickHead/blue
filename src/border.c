/*!
    @file border.c

    @brief SOURCE_BRIEF

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

    @file border.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "border.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

border_s *border_create(void)
{
  border_s *b;

  b = (border_s *)malloc(sizeof(border_s));
  memset(b, 0, sizeof(border_s));

  b->units = units_type_mm;
  b->line_width = 1.0;
  b->margins = margins_create();

  b->background_color = color_create();
  color_set_tag(b->background_color, "background-color");
  color_white(b->background_color);

  b->line_color = color_create();
  color_set_tag(b->line_color, "line-color");
  color_black(b->line_color);

    // Return RETVAL
  return b;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void border_destroy(border_s *b)
{
    // Sanity check parameters.
  assert(b);
  if (b->margins) margins_destroy(b->margins);
  if (b->background_color) color_destroy(b->background_color);
  if (b->line_color) color_destroy(b->line_color);
  free(b);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

border_s *border_copy(border_s *b)
{
  border_s *nb;

    // Sanity check parameters.
  assert(b);

  nb = border_create();
  memcpy(nb, b, sizeof(border_s));

  if (b->margins) nb->margins = margins_copy(b->margins);
  if (b->background_color) nb->background_color = color_copy(b->background_color);
  if (b->line_color) nb->line_color = color_copy(b->line_color);

    // Return RETVAL
  return nb;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void border_set(border_s *b,
                units_t units,
                double line_width,
                margins_s *margins,
                color_s *background_color,
                color_s *line_color)
{
    // Sanity check parameters.
  assert(b);
  assert(margins);
  assert(background_color);
  assert(line_color);

  border_set_units(b, units);
  border_set_line_width(b, line_width);
  border_set_margins(b, margins);
  border_set_background_color(b, background_color);
  border_set_line_color(b, line_color);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void border_get(border_s *b,
                units_t *units,
                double *line_width,
                margins_s **margins,
                color_s **background_color,
                color_s **line_color)
{
    // Sanity check parameters.
  assert(b);
  assert(units);
  assert(line_width);
  assert(margins);
  assert(background_color);
  assert(line_color);

  *units = border_get_units(b);
  *line_width = border_get_line_width(b);
  *margins = border_get_margins(b);
  *background_color = border_get_background_color(b);
  *line_color = border_get_line_color(b);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void border_set_units(border_s *b, units_t ut)
{
  units_t old_ut;

    // Sanity check parameters.
  assert(b);

  old_ut = b->units;
  b->units = ut;
  b->line_width = units_convert(b->line_width, old_ut, b->units);
  if (b->margins->units == old_ut)
    margins_set_units(b->margins, ut);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

units_t border_get_units(border_s *b)
{
    // Sanity check parameters.
  assert(b);
    // Return RETVAL
  return b->units;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void border_set_line_width(border_s *b, double lw)
{
    // Sanity check parameters.
  assert(b);
  b->line_width = lw;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double border_get_line_width(border_s *b)
{
    // Sanity check parameters.
  assert(b);
    // Return RETVAL
  return b->line_width;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void border_set_margins(border_s *b, margins_s *m)
{
    // Sanity check parameters.
  assert(b);
  assert(m);
  if (b->margins) margins_destroy(b->margins);
  b->margins = m;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

margins_s *border_get_margins(border_s *b)
{
    // Sanity check parameters.
  assert(b);
    // Return RETVAL
  return b->margins;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void border_set_background_color(border_s *b, color_s *background_color)
{
    // Sanity check parameters.
  assert(b);
  assert(background_color);
  if (b->background_color) color_destroy(b->background_color);
  b->background_color = background_color;
  color_set_tag(b->background_color, "background-color");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

color_s *border_get_background_color(border_s *b)
{
    // Sanity check parameters.
  assert(b);
    // Return RETVAL
  return b->background_color;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void border_set_line_color(border_s *b, color_s *line_color)
{
    // Sanity check parameters.
  assert(b);
  assert(line_color);
  if (b->line_color) color_destroy(b->line_color);
  b->line_color = line_color;
  color_set_tag(b->line_color, "line-color");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

color_s *border_get_line_color(border_s *b)
{
    // Sanity check parameters.
  assert(b);
    // Return RETVAL
  return b->line_color;
}

