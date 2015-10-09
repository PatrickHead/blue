/*!
    @file design-elliptic.c

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

    @file design-elliptic.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "reference.h"

#include "design-elliptic.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_elliptic_s *design_elliptic_create(void)
{
  design_elliptic_s *elliptic;

  elliptic = (design_elliptic_s *)malloc(sizeof(design_elliptic_s));
  memset(elliptic, 0, sizeof(design_elliptic_s));

  elliptic->center = vertex_create();
  if (elliptic->center) vertex_set(elliptic->center, "center", 0.0, 0.0, 0.0);

    // Return RETVAL
  return elliptic;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_destroy(design_elliptic_s *e)
{
    // Sanity check parameters.
  assert(e);
  if (e->center) vertex_destroy(e->center);
  free(e);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_elliptic_s *design_elliptic_copy(design_elliptic_s *e)
{
  design_elliptic_s *ne;

    // Sanity check parameters.
  assert(e);

  ne = design_elliptic_create();
  memcpy(ne, e, sizeof(design_elliptic_s));

  if (e->center) ne->center = vertex_copy(e->center);

    // Return RETVAL
  return ne;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_set(design_elliptic_s *e,
                         vertex_s *center,
                         double width,
                         double height,
                         double rotation,
                         double start_angle,
                         double end_angle)
{
    // Sanity check parameters.
  assert(e);
  assert(center);

  design_elliptic_set_center(e, center);
  design_elliptic_set_width(e, width);
  design_elliptic_set_height(e, height);
  design_elliptic_set_rotation(e, rotation);
  design_elliptic_set_start_angle(e, start_angle);
  design_elliptic_set_end_angle(e, end_angle);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_get(design_elliptic_s *e,
                         vertex_s **center,
                         double *width,
                         double *height,
                         double *rotation,
                         double *start_angle,
                         double *end_angle)
{
    // Sanity check parameters.
  assert(e);
  assert(center);
  assert(width);
  assert(height);
  assert(rotation);
  assert(start_angle);
  assert(end_angle);

  *center = design_elliptic_get_center(e);
  *width = design_elliptic_get_width(e);
  *height = design_elliptic_get_height(e);
  *rotation = design_elliptic_get_rotation(e);
  *start_angle = design_elliptic_get_start_angle(e);
  *end_angle = design_elliptic_get_end_angle(e);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_set_center(design_elliptic_s *e, vertex_s *center)
{
    // Sanity check parameters.
  assert(e);
  assert(center);
  if (e->center) vertex_destroy(e->center);
  e->center = center;
  vertex_set_tag(e->center, "center");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_elliptic_get_center(design_elliptic_s *e)
{
    // Sanity check parameters.
  assert(e);
    // Return RETVAL
  return e->center;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_set_width(design_elliptic_s *e, double width)
{
    // Sanity check parameters.
  assert(e);
  e->width = width;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_elliptic_get_width(design_elliptic_s *e)
{
    // Sanity check parameters.
  assert(e);
    // Return RETVAL
  return e->width;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_set_height(design_elliptic_s *e, double height)
{
    // Sanity check parameters.
  assert(e);
  e->height = height;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_elliptic_get_height(design_elliptic_s *e)
{
    // Sanity check parameters.
  assert(e);
    // Return RETVAL
  return e->height;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_set_rotation(design_elliptic_s *e, double rotation)
{
    // Sanity check parameters.
  assert(e);
  e->rotation = rotation;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_elliptic_get_rotation(design_elliptic_s *e)
{
    // Sanity check parameters.
  assert(e);
    // Return RETVAL
  return e->rotation;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_set_start_angle(design_elliptic_s *e, double start_angle)
{
    // Sanity check parameters.
  assert(e);
  e->start_angle = start_angle;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_elliptic_get_start_angle(design_elliptic_s *e)
{
    // Sanity check parameters.
  assert(e);
    // Return RETVAL
  return e->start_angle;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elliptic_set_end_angle(design_elliptic_s *e, double end_angle)
{
    // Sanity check parameters.
  assert(e);
  e->end_angle = end_angle;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_elliptic_get_end_angle(design_elliptic_s *e)
{
    // Sanity check parameters.
  assert(e);
    // Return RETVAL
  return e->end_angle;
}

