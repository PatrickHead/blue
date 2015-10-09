/*!
    @file design-point.c

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

    @file design-point.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "reference.h"

#include "design-point.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_point_s *design_point_create(void)
{
  design_point_s *point;

  point = (design_point_s *)malloc(sizeof(design_point_s));
  memset(point, 0, sizeof(design_point_s));

  point->location = vertex_create();
  if (point->location) vertex_set(point->location, "location", 0.0, 0.0, 0.0);

    // Return RETVAL
  return point;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_point_destroy(design_point_s *p)
{
    // Sanity check parameters.
  assert(p);
  if (p->location) vertex_destroy(p->location);
  free(p);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_point_s *design_point_copy(design_point_s *p)
{
  design_point_s *np;

    // Sanity check parameters.
  assert(p);

  np = design_point_create();
  memcpy(np, p, sizeof(design_point_s));

  if (p->location) np->location = vertex_copy(p->location);

    // Return RETVAL
  return np;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_point_set(design_point_s *p,
                      vertex_s *location)
{
    // Sanity check parameters.
  assert(p);
  assert(location);

  design_point_set_location(p, location);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_point_get(design_point_s *p,
                      vertex_s **location)
{
    // Sanity check parameters.
  assert(p);
  assert(location);

  *location = design_point_get_location(p);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_point_set_location(design_point_s *p, vertex_s *location)
{
    // Sanity check parameters.
  assert(p);
  assert(location);
  if (p->location) vertex_destroy(p->location);
  p->location = location;
  vertex_set_tag(p->location, "location");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_point_get_location(design_point_s *p)
{
    // Sanity check parameters.
  assert(p);
    // Return RETVAL
  return p->location;
}

