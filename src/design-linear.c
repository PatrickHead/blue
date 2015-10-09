/*!
    @file design-linear.c

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

    @file design-linear.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "reference.h"

#include "design-defaults.h"

#include "design-linear.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_linear_s *design_linear_create(void)
{
  design_linear_s *linear;
  design_defaults_s *d;

  linear = (design_linear_s *)malloc(sizeof(design_linear_s));
  memset(linear, 0, sizeof(design_linear_s));

  d = design_defaults_current();
  if (d)
  {
    linear->gap = d->linear_gap;
    linear->extension_above = d->linear_extension_above;
    linear->extension_below = d->linear_extension_below;
  }

  linear->start = vertex_create();
  if (linear->start) vertex_set(linear->start, "start", 0.0, 0.0, 0.0);

  linear->end = vertex_create();
  if (linear->end) vertex_set(linear->end, "end", 0.0, 0.0, 0.0);

    // Return RETVAL
  return linear;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_destroy(design_linear_s *l)
{
    // Sanity check parameters.
  assert(l);
  if (l->start) vertex_destroy(l->start);
  if (l->end) vertex_destroy(l->end);
  free(l);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_linear_s *design_linear_copy(design_linear_s *l)
{
  design_linear_s *nl;

    // Sanity check parameters.
  assert(l);

  nl = design_linear_create();
  memcpy(nl, l, sizeof(design_linear_s));

  if (l->start) nl->start = vertex_copy(l->start);
  if (l->end) nl->end = vertex_copy(l->end);

    // Return RETVAL
  return nl;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_set(design_linear_s *l,
                       vertex_s *start,
                       vertex_s *end,
                       double gap,
                       double extension_above,
                       double extension_below,
                       double dimension)
{
    // Sanity check parameters.
  assert(l);
  assert(start);
  assert(end);

  design_linear_set_start(l, start);
  design_linear_set_end(l, end);
  design_linear_set_gap(l, gap);
  design_linear_set_extension_above(l, extension_above);
  design_linear_set_extension_below(l, extension_below);
  design_linear_set_dimension(l, dimension);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_get(design_linear_s *l,
                       vertex_s **start,
                       vertex_s **end,
                       double *gap,
                       double *extension_above,
                       double *extension_below,
                       double *dimension)
{
    // Sanity check parameters.
  assert(l);
  assert(start);
  assert(end);
  assert(gap);
  assert(extension_above);
  assert(extension_below);
  assert(dimension);

  *start = design_linear_get_start(l);
  *end = design_linear_get_end(l);
  *gap = design_linear_get_gap(l);
  *extension_above = design_linear_get_extension_above(l);
  *extension_below = design_linear_get_extension_below(l);
  *dimension = design_linear_get_dimension(l);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_set_start(design_linear_s *l, vertex_s *start)
{
    // Sanity check parameters.
  assert(l);
  assert(start);
  if (l->start) vertex_destroy(l->start);
  l->start = start;
  vertex_set_tag(l->start, "start");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_linear_get_start(design_linear_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->start;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_set_end(design_linear_s *l, vertex_s *end)
{
    // Sanity check parameters.
  assert(l);
  assert(end);
  if (l->end) vertex_destroy(l->end);
  l->end = end;
  vertex_set_tag(l->end, "end");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_linear_get_end(design_linear_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->end;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_set_gap(design_linear_s *l, double gap)
{
    // Sanity check parameters.
  assert(l);
  l->gap = gap;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_linear_get_gap(design_linear_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->gap;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_set_extension_above(design_linear_s *l, double extension_above)
{
    // Sanity check parameters.
  assert(l);
  l->extension_above = extension_above;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_linear_get_extension_above(design_linear_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->extension_above;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_set_extension_below(design_linear_s *l, double extension_below)
{
    // Sanity check parameters.
  assert(l);
  l->extension_below = extension_below;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_linear_get_extension_below(design_linear_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->extension_below;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_linear_set_dimension(design_linear_s *l, double dimension)
{
    // Sanity check parameters.
  assert(l);
  l->dimension = dimension;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_linear_get_dimension(design_linear_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->dimension;
}

