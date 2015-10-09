/*!
    @file design-radial.c

    @brief SOURCE_BRIEF

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

    @file design-radial.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "reference.h"

#include "design-radial.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_radial_s *design_radial_create(void)
{
  design_radial_s *radial;

  radial = (design_radial_s *)malloc(sizeof(design_radial_s));
  memset(radial, 0, sizeof(design_radial_s));

  radial->center = vertex_create();
  if (radial->center) vertex_set(radial->center, "center", 0.0, 0.0, 0.0);

    // Return RETVAL
  return radial;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_destroy(design_radial_s *r)
{
    // Sanity check parameters.
  assert(r);
  if (r->center) vertex_destroy(r->center);
  free(r);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_radial_s *design_radial_copy(design_radial_s *r)
{
  design_radial_s *nr;

    // Sanity check parameters.
  assert(r);

  nr = design_radial_create();
  memcpy(nr, r, sizeof(design_radial_s));

  if (r->center) nr->center = vertex_copy(r->center);

    // Return RETVAL
  return nr;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_set(design_radial_s *r,
                       design_radial_t type,
                       vertex_s *center,
                       double major,
                       double minor,
                       double angle,
                       double leader)
{
    // Sanity check parameters.
  assert(r);
  assert(center);

  design_radial_set_type(r, type);
  design_radial_set_center(r, center);
  design_radial_set_major(r, major);
  design_radial_set_minor(r, minor);
  design_radial_set_angle(r, angle);
  design_radial_set_leader(r, type);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_get(design_radial_s *r,
                       design_radial_t *type,
                       vertex_s **center,
                       double *major,
                       double *minor,
                       double *angle,
                       double *leader)
{
    // Sanity check parameters.
  assert(r);
  assert(type);
  assert(center);
  assert(major);
  assert(minor);
  assert(angle);
  assert(leader);

  *type = design_radial_get_type(r);
  *center = design_radial_get_center(r);
  *major = design_radial_get_major(r);
  *minor = design_radial_get_minor(r);
  *angle = design_radial_get_angle(r);
  *leader = design_radial_get_leader(r);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_set_type(design_radial_s *r, design_radial_t type)
{
    // Sanity check parameters.
  assert(r);
  r->type = type;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_radial_t design_radial_get_type(design_radial_s *r)
{
    // Sanity check parameters.
  assert(r);
    // Return RETVAL
  return r->type;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_set_center(design_radial_s *r, vertex_s *center)
{
    // Sanity check parameters.
  assert(r);
  if (r->center) vertex_destroy(r->center);
  r->center = center;
  vertex_set_tag(r->center, "center");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_radial_get_center(design_radial_s *r)
{
    // Sanity check parameters.
  assert(r);
    // Return RETVAL
  return r->center;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_set_major(design_radial_s *r, double major)
{
    // Sanity check parameters.
  assert(r);
  r->major = major;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_radial_get_major(design_radial_s *r)
{
    // Sanity check parameters.
  assert(r);
    // Return RETVAL
  return r->major;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_set_minor(design_radial_s *r, double minor)
{
    // Sanity check parameters.
  assert(r);
  r->minor = minor;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_radial_get_minor(design_radial_s *r)
{
    // Sanity check parameters.
  assert(r);
    // Return RETVAL
  return r->minor;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_set_angle(design_radial_s *r, double angle)
{
    // Sanity check parameters.
  assert(r);
  r->angle = angle;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_radial_get_angle(design_radial_s *r)
{
    // Sanity check parameters.
  assert(r);
    // Return RETVAL
  return r->angle;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_radial_set_leader(design_radial_s *r, double leader)
{
    // Sanity check parameters.
  assert(r);
  r->leader = leader;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_radial_get_leader(design_radial_s *r)
{
    // Sanity check parameters.
  assert(r);
    // Return RETVAL
  return r->leader;
}

