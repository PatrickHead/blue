/*!
    @file design-elliptic.h

    @brief Header file for design elliptic element structure

    @timestamp Fri, 28 Nov 2014 17:52:12 +0000

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

    @file design-elliptic.h

    @brief Header file for design elliptic element structure

    Structure and maintenance functions for design elliptic element.

  */

#ifndef DESIGN_ELLIPTIC_H
#define DESIGN_ELLIPTIC_H

  // External include files

#include "vertex.h"

  /*!
    @brief Design elliptic element structure
  */

typedef struct
{
    /*! @brief Center point of elliptic curve */
  vertex_s *center;
    /*! @brief Width of elliptic curve */
  double width;
    /*! @brief Height of elliptic curve */
  double height;
    /*! @brief Rotation of elliptic curve, in degrees */
  double rotation;
    /*! @brief Starting point of drawn elliptic curve, in degrees */
  double start_angle;
    /*! @brief Ending point of drawn elliptic curve, in degrees */
  double end_angle;
} design_elliptic_s;

  // Structure maintenance functions

design_elliptic_s *design_elliptic_create(void);
void design_elliptic_destroy(design_elliptic_s *e);
design_elliptic_s *design_elliptic_copy(design_elliptic_s *e);

  // Comprehensive getter/setter

void design_elliptic_set(design_elliptic_s *e,
                         vertex_s *center,
                         double width,
                         double height,
                         double rotation,
                         double start_angle,
                         double end_angle);
void design_elliptic_get(design_elliptic_s *e,
                         vertex_s **center,
                         double *width,
                         double *height,
                         double *rotation,
                         double *start_angle,
                         double *end_angle);

  // Individual getters/setters

void design_elliptic_set_center(design_elliptic_s *e, vertex_s *center); 
vertex_s *design_elliptic_get_center(design_elliptic_s *e);

void design_elliptic_set_width(design_elliptic_s *e, double width); 
double design_elliptic_get_width(design_elliptic_s *e);

void design_elliptic_set_height(design_elliptic_s *e, double height); 
double design_elliptic_get_height(design_elliptic_s *e);

void design_elliptic_set_rotation(design_elliptic_s *e, double rotation); 
double design_elliptic_get_rotation(design_elliptic_s *e);

void design_elliptic_set_start_angle(design_elliptic_s *e, double start_angle); 
double design_elliptic_get_start_angle(design_elliptic_s *e);

void design_elliptic_set_end_angle(design_elliptic_s *e, double end_angle); 
double design_elliptic_get_end_angle(design_elliptic_s *e);

#endif // DESIGN_ELLIPTIC_H
