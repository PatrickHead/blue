/*!
    @file margins.h

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

    @file margins.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef MARGINS_H
#define MARGINS_H

#include "units.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  units_t units;
    /*! @brief ELEMENT_BRIEF */
  double left;
    /*! @brief ELEMENT_BRIEF */
  double right;
    /*! @brief ELEMENT_BRIEF */
  double top;
    /*! @brief ELEMENT_BRIEF */
  double bottom;
} margins_s;

margins_s *margins_create(void);
void margins_destroy(margins_s *m);
margins_s *margins_copy(margins_s *m);

void margins_set(margins_s *m,
                 units_t units,
                 double left,
                 double right,
                 double top,
                 double bottom);
void margins_get(margins_s *m,
                 units_t *units,
                 double *left,
                 double *right,
                 double *top,
                 double *bottom);

void margins_set_units(margins_s *m, units_t u);
units_t margins_get_units(margins_s *m);

void margins_set_left(margins_s *m, double l);
double margins_get_left(margins_s *m);

void margins_set_right(margins_s *m, double r);
double margins_get_right(margins_s *m);

void margins_set_top(margins_s *m, double t);
double margins_get_top(margins_s *m);

void margins_set_bottom(margins_s *m, double b);
double margins_get_bottom(margins_s *m);

#endif // MARGINS_H
