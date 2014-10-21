/*!
    @file design-tolerance.h

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

    @file design-tolerance.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_TOLERANCE_H
#define DESIGN_TOLERANCE_H

#include "vertex.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! brief ELEMENT_BRIEF */
  vertex_s *location;
    /*! brief ELEMENT_BRIEF */
  double text_size;
    /*! brief ELEMENT_BRIEF */
  double plus;
    /*! brief ELEMENT_BRIEF */
  double minus;
    /*! brief ELEMENT_BRIEF */
  int precision;
} design_tolerance_s;

design_tolerance_s *design_tolerance_create(void);
void design_tolerance_destroy(design_tolerance_s *t);
design_tolerance_s *design_tolerance_copy(design_tolerance_s *t);

void design_tolerance_set(design_tolerance_s *t,
                          vertex_s *location,
                          double text_size,
                          double plus,
                          double minus,
                          int precision);
void design_tolerance_get(design_tolerance_s *t,
                          vertex_s **location,
                          double *text_size,
                          double *plus,
                          double *minus,
                          int *precision);

void design_tolerance_set_location(design_tolerance_s *t, vertex_s *location); 
vertex_s *design_tolerance_get_location(design_tolerance_s *t);

void design_tolerance_set_text_size(design_tolerance_s *t, double text_size); 
double design_tolerance_get_text_size(design_tolerance_s *t);

void design_tolerance_set_plus(design_tolerance_s *t, double plus); 
double design_tolerance_get_plus(design_tolerance_s *t);

void design_tolerance_set_minus(design_tolerance_s *t, double minus); 
double design_tolerance_get_minus(design_tolerance_s *t);

void design_tolerance_set_precision(design_tolerance_s *t, int precision); 
int design_tolerance_get_precision(design_tolerance_s *t);

#endif // DESIGN_TOLERANCE_H
