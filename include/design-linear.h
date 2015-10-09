/*!
    @file design-linear.h

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

    @file design-linear.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_LINEAR_H
#define DESIGN_LINEAR_H

#include "vertex.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  vertex_s *start;
    /*! @brief ELEMENT_BRIEF */
  vertex_s *end;
    /*! @brief ELEMENT_BRIEF */
  double gap;
    /*! @brief ELEMENT_BRIEF */
  double extension_above;
    /*! @brief ELEMENT_BRIEF */
  double extension_below;
  double dimension; // 0 is automatic
} design_linear_s;

design_linear_s *design_linear_create(void);
void design_linear_destroy(design_linear_s *l);
design_linear_s *design_linear_copy(design_linear_s *l);

void design_linear_set(design_linear_s *l,
                       vertex_s *start,
                       vertex_s *end,
                       double gap,
                       double extension_above,
                       double extension_below,
                       double dimension);
void design_linear_get(design_linear_s *l,
                       vertex_s **start,
                       vertex_s **end,
                       double *gap,
                       double *extension_above,
                       double *extension_below,
                       double *dimension);

void design_linear_set_start(design_linear_s *l, vertex_s *start); 
vertex_s *design_linear_get_start(design_linear_s *l);
void design_linear_set_end(design_linear_s *l, vertex_s *end); 
vertex_s *design_linear_get_end(design_linear_s *l);
void design_linear_set_gap(design_linear_s *l, double gap); 
double design_linear_get_gap(design_linear_s *l);
void design_linear_set_extension_above(design_linear_s *l,
                                       double extension_above); 
double design_linear_get_extension_above(design_linear_s *l);
void design_linear_set_extension_below(design_linear_s *l,
                                       double extension_below); 
double design_linear_get_extension_below(design_linear_s *l);
void design_linear_set_dimension(design_linear_s *l, double dimension); 
double design_linear_get_dimension(design_linear_s *l);

#endif // DESIGN_LINEAR_H
