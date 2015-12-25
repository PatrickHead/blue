/*!
    @file design-dimension.h

    @brief Header file for design dimension element structure

    @timestamp Fri, 09 Oct 2015 05:38:21 +0000

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

    @brief Header file for design dimension element structure

    Structure and maintenance functions for design dimension element.

  */

#ifndef DESIGN_DIMENSION_H
#define DESIGN_DIMENSION_H

  // External include files

#include "vertex.h"

  // Project specific include files

#include "design-dimension-type.h"
#include "design-linear.h"
#include "design-angular.h"
#include "design-radial.h"

  /*!
    @brief Design dimension structure
  */

typedef struct
{
    /*! @brief Type of dimension */
  design_dimension_t type;
    /*! @brief Size of text rendered in dimension element */
  double text_size;
    /*! @brief Location of text */
  vertex_s *text_location;
    /*! @brief Precision of dimension */
  int precision;
  union
  {
    /*! @brief Data for linear type dimensions */
    design_linear_s *linear;
    /*! @brief Data for angular type dimensions */
    design_angular_s *angular;
    /*! @brief Data for radial type dimensions */
    design_radial_s *radial;
  };
} design_dimension_s;

  // Structure maintenance functions

design_dimension_s *design_dimension_create(void);
void design_dimension_destroy(design_dimension_s *d);
design_dimension_s *design_dimension_copy(design_dimension_s *d);

  // Comprehensive getter/setter

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

  // Individual getters/setters

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

void design_dimension_set_linear(design_dimension_s *d,
                                 design_linear_s *linear); 
design_linear_s *design_dimension_get_linear(design_dimension_s *d);

void design_dimension_set_angular(design_dimension_s *d,
                                  design_angular_s *angular); 
design_angular_s *design_dimension_get_angular(design_dimension_s *d);

void design_dimension_set_radial(design_dimension_s *d,
                                 design_radial_s *radial); 
design_radial_s *design_dimension_get_radial(design_dimension_s *d);

#endif // DESIGN_DIMENSION_H
