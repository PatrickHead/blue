/*!
    @file design-polyline.c

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

    @file design-polyline.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "reference.h"

#include "design-polyline.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_polyline_s *design_polyline_create(void)
{
  design_polyline_s *polyline;

  polyline = (design_polyline_s *)malloc(sizeof(design_polyline_s));
  memset(polyline, 0, sizeof(design_polyline_s));

  polyline->vertices = vertices_create();

    // Return RETVAL
  return polyline;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_polyline_destroy(design_polyline_s *pl)
{
    // Sanity check parameters.
  assert(pl);
  if (pl->vertices) vertices_destroy(pl->vertices);
  free(pl);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_polyline_s *design_polyline_copy(design_polyline_s *pl)
{
  design_polyline_s *npl;

    // Sanity check parameters.
  assert(pl);

  npl = design_polyline_create();
  memcpy(npl, pl, sizeof(design_polyline_s));

  if (pl->vertices) npl->vertices = vertices_copy(pl->vertices);

    // Return RETVAL
  return npl;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_polyline_set(design_polyline_s *pl, vertices_s *vertices)
{
    // Sanity check parameters.
  assert(pl);
  assert(vertices);

  design_polyline_set_vertices(pl, vertices);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_polyline_get(design_polyline_s *pl, vertices_s **vertices)
{
    // Sanity check parameters.
  assert(pl);
  assert(vertices);

  *vertices = design_polyline_get_vertices(pl);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_polyline_set_vertices(design_polyline_s *pl, vertices_s *vertices)
{
    // Sanity check parameters.
  assert(pl);
  assert(vertices);
  if (pl->vertices) vertices_destroy(pl->vertices);
  pl->vertices = vertices;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertices_s *design_polyline_get_vertices(design_polyline_s *pl)
{
    // Sanity check parameters.
  assert(pl);
    // Return RETVAL
  return pl->vertices;
}

