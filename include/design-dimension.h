/*!
    @file design-dimension.h

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

    @file design-dimension.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_DIMENSION_H
#define DESIGN_DIMENSION_H

#include "vertex.h"

#include "design-dimension-type.h"
#include "design-linear.h"
#include "design-angular.h"
#include "design-radial.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! brief ELEMENT_BRIEF */
  design_dimension_t type;
    /*! brief ELEMENT_BRIEF */
  double text_size;
    /*! brief ELEMENT_BRIEF */
  vertex_s *text_location;
    /*! brief ELEMENT_BRIEF */
  int precision;
  union
  {
    /*! brief ELEMENT_BRIEF */
    design_linear_s *linear;
    /*! brief ELEMENT_BRIEF */
    design_angular_s *angular;
    /*! brief ELEMENT_BRIEF */
    design_radial_s *radial;
    /*! brief ELEMENT_BRIEF */
  };
} design_dimension_s;

design_dimension_s *design_dimension_create(void);
void design_dimension_destroy(design_dimension_s *d);
design_dimension_s *design_dimension_copy(design_dimension_s *d);

void design_dimension_set(design_dimension_s *d,
                          design_dimension_t type,
                          double text_size,
                          vertex_s *text_location,
                          int precision,
                          void *data);
void design_dimension_get(design_dimension_s *d,
                          design_dimension_t *type,
                          double *text_size,
                          vertex_s **text_location,
                          int *precision,
                          void **data);

void design_dimension_set_type(design_dimension_s *d,
                               design_dimension_t type); 
design_dimension_t design_dimension_get_type(design_dimension_s *d);
void design_dimension_set_text_size(design_dimension_s *d, double text_size); 
double design_dimension_get_text_size(design_dimension_s *d);
void design_dimension_set_text_location(design_dimension_s *d,
                                        vertex_s *text_location); 
vertex_s *design_dimension_get_text_location(design_dimension_s *d);
void design_dimension_set_precision(design_dimension_s *d, int precision); 
int design_dimension_get_precision(design_dimension_s *d);
void design_dimension_set_linear(design_dimension_s *d, design_linear_s *linear); 
design_linear_s *design_dimension_get_linear(design_dimension_s *d);
void design_dimension_set_angular(design_dimension_s *d,
                                  design_angular_s *angular); 
design_angular_s *design_dimension_get_angular(design_dimension_s *d);
void design_dimension_set_radial(design_dimension_s *d, design_radial_s *radial); 
design_radial_s *design_dimension_get_radial(design_dimension_s *d);

#endif // DESIGN_DIMENSION_H
