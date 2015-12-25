/*!
    @file design-spline.c

    @brief SOURCE_BRIEF

    @timestamp Sun, 20 Dec 2015 12:31:00 +0000

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

    @file design-spline.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "reference.h"

#include "design-spline.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_spline_s *design_spline_create(void)
{
  design_spline_s *spline;

  spline = (design_spline_s *)malloc(sizeof(design_spline_s));
  memset(spline, 0, sizeof(design_spline_s));

  spline->vertices = vertices_create();

    // Return RETVAL
  return spline;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_spline_destroy(design_spline_s *s)
{
    // Sanity check parameters.
  assert(s);
  if (s->vertices) vertices_destroy(s->vertices);
  free(s);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_spline_s *design_spline_copy(design_spline_s *s)
{
  design_spline_s *ns;

    // Sanity check parameters.
  assert(s);

  ns = design_spline_create();
  memcpy(ns, s, sizeof(design_spline_s));

  if (s->vertices) ns->vertices = vertices_copy(s->vertices);

    // Return RETVAL
  return ns;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_spline_set(design_spline_s *s, vertices_s *vertices)
{
    // Sanity check parameters.
  assert(s);
  assert(vertices);

  design_spline_set_vertices(s, vertices);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_spline_get(design_spline_s *s, vertices_s **vertices)
{
    // Sanity check parameters.
  assert(s);
  assert(vertices);

  *vertices = design_spline_get_vertices(s);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_spline_set_vertices(design_spline_s *s, vertices_s *vertices)
{
    // Sanity check parameters.
  assert(s);
  assert(vertices);
  if (s->vertices) vertices_destroy(s->vertices);
  s->vertices = vertices_copy(vertices);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertices_s *design_spline_get_vertices(design_spline_s *s)
{
    // Sanity check parameters.
  assert(s);
    // Return RETVAL
  return s->vertices;
}

