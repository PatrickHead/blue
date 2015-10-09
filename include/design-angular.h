/*!
    @file design-angular.h

    @brief Header file for design angular type definition.

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

    @file design-angular.h

    @brief Header file for design angular type definition.

    Structure and maintenance functions for angular measurements.

  */

#ifndef DESIGN_ANGULAR_H
#define DESIGN_ANGULAR_H

  // External include files

#include "vertex.h"

  /*!
    @brief Design angular measurement parameters
  */

typedef struct
{
    /*! @brief displayed angle of measurment, '0' is automatic */
  double angle;
    /*! @brief vertex of measured angle, command endpoint to line segments */
  vertex_s *alpha;
    /*! @brief endpoint of alpha.beta line segment */
  vertex_s *beta;
    /*! @brief endpoint of alpha.gamma line segment */
  vertex_s *gamma;
    /*! @brief gap between extension lines and angle of measurement */
  double gap;
    /*! @brief length of extension lines */
  double extension;
} design_angular_s;

  // Structure management functions

design_angular_s *design_angular_create(void);
void design_angular_destroy(design_angular_s *a);
design_angular_s *design_angular_copy(design_angular_s *a);

  // Comprehensive getter/setter

void design_angular_set(design_angular_s *a,
                        double angle,
                        vertex_s *alpha,
                        vertex_s *beta,
                        vertex_s *gamma,
                        double gap,
                        double extension);
void design_angular_get(design_angular_s *a,
                        double *angle,
                        vertex_s **alpha,
                        vertex_s **beta,
                        vertex_s **gamma,
                        double *gap,
                        double *extension);

  // Individual getters/setters

void design_angular_set_angle(design_angular_s *a, double angle); 
double design_angular_get_angle(design_angular_s *a);

void design_angular_set_alpha(design_angular_s *a, vertex_s *alpha); 
vertex_s *design_angular_get_alpha(design_angular_s *a);

void design_angular_set_beta(design_angular_s *a, vertex_s *beta); 
vertex_s *design_angular_get_beta(design_angular_s *a);

void design_angular_set_gamma(design_angular_s *a, vertex_s *gamma); 
vertex_s *design_angular_get_gamma(design_angular_s *a);

void design_angular_set_gap(design_angular_s *a, double gap); 
double design_angular_get_gap(design_angular_s *a);

void design_angular_set_extension(design_angular_s *a, double extension); 
double design_angular_get_extension(design_angular_s *a);

#endif // DESIGN_ANGULAR_H
