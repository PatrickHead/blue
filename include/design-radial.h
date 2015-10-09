/*!
    @file design-radial.h

    @brief HEADER_BRIEF

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

    @file design-radial.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_RADIAL_H
#define DESIGN_RADIAL_H

#include "vertex.h"

#include "design-radial-type.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  design_radial_t type;
  vertex_s *center; // center point of elliptic arc
  double major;  // major radius of elliptic arc, or only radius for circular arc
  double minor;  // minor radius of elliptic arc
  double angle;  // angle of leader, absolute in degrees
  double leader; // length of leader
} design_radial_s;

design_radial_s *design_radial_create(void);
void design_radial_destroy(design_radial_s *r);
design_radial_s *design_radial_copy(design_radial_s *r);

void design_radial_set(design_radial_s *r,
                       design_radial_t type,
                       vertex_s *center,
                       double major,
                       double minor,
                       double angle,
                       double leader);
void design_radial_get(design_radial_s *r,
                       design_radial_t *type,
                       vertex_s **center,
                       double *major,
                       double *minor,
                       double *angle,
                       double *leader);

void design_radial_set_type(design_radial_s *r, design_radial_t type); 
design_radial_t design_radial_get_type(design_radial_s *r);
void design_radial_set_center(design_radial_s *r, vertex_s *center); 
vertex_s *design_radial_get_center(design_radial_s *r);
void design_radial_set_major(design_radial_s *r, double major); 
double design_radial_get_major(design_radial_s *r);
void design_radial_set_minor(design_radial_s *r, double minor); 
double design_radial_get_minor(design_radial_s *r);
void design_radial_set_angle(design_radial_s *r, double angle); 
double design_radial_get_angle(design_radial_s *r);
void design_radial_set_leader(design_radial_s *r, double leader); 
double design_radial_get_leader(design_radial_s *r);

#endif // DESIGN_RADIAL_H
