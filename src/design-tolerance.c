/*!
    @file design-tolerance.c

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

    @file design-tolerance.c

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

#include "design-tolerance.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_tolerance_s *design_tolerance_create(void)
{
  design_tolerance_s *tolerance;
  design_defaults_s *d;

  tolerance = (design_tolerance_s *)malloc(sizeof(design_tolerance_s));
  memset(tolerance, 0, sizeof(design_tolerance_s));

  d = design_defaults_current();
  if (d)
  {
    tolerance->text_size = d->tolerance_text_size;
    tolerance->plus = d->tolerance_plus;
    tolerance->minus = d->tolerance_minus;
    tolerance->precision = d->tolerance_precision;
  }

  tolerance->location = vertex_create();
  if (tolerance->location)
    vertex_set(tolerance->location, "location", 0.0, 0.0, 0.0);

    // Return RETVAL
  return tolerance;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_tolerance_destroy(design_tolerance_s *t)
{
    // Sanity check parameters.
  assert(t);
  if (t->location) vertex_destroy(t->location);
  free(t);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_tolerance_s *design_tolerance_copy(design_tolerance_s *t)
{
  design_tolerance_s *nt;

    // Sanity check parameters.
  assert(t);

  nt = design_tolerance_create();
  memcpy(nt, t, sizeof(design_tolerance_s));

  if (t->location) nt->location = vertex_copy(t->location);

    // Return RETVAL
  return nt;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_tolerance_set(design_tolerance_s *t,
                          vertex_s *location,
                          double text_size,
                          double plus,
                          double minus,
                          int precision)
{
    // Sanity check parameters.
  assert(t);
  assert(location);

  design_tolerance_set_location(t, location);
  design_tolerance_set_text_size(t, text_size);
  design_tolerance_set_plus(t, plus);
  design_tolerance_set_minus(t, minus);
  design_tolerance_set_precision(t, precision);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_tolerance_get(design_tolerance_s *t,
                          vertex_s **location,
                          double *text_size,
                          double *plus,
                          double *minus,
                          int *precision)
{
    // Sanity check parameters.
  assert(t);
  assert(location);
  assert(text_size);
  assert(plus);
  assert(minus);
  assert(precision);

  *location = design_tolerance_get_location(t);
  *text_size = design_tolerance_get_text_size(t);
  *plus = design_tolerance_get_plus(t);
  *minus = design_tolerance_get_minus(t);
  *precision = design_tolerance_get_precision(t);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_tolerance_set_location(design_tolerance_s *t, vertex_s *location)
{
    // Sanity check parameters.
  assert(t);
  assert(location);
  if (t->location) vertex_destroy(t->location);
  t->location = location;
  vertex_set_tag(t->location, "location");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_tolerance_get_location(design_tolerance_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->location;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_tolerance_set_text_size(design_tolerance_s *t, double text_size)
{
    // Sanity check parameters.
  assert(t);
  t->text_size = text_size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_tolerance_get_text_size(design_tolerance_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->text_size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_tolerance_set_plus(design_tolerance_s *t, double plus)
{
    // Sanity check parameters.
  assert(t);
  t->plus = plus;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_tolerance_get_plus(design_tolerance_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->plus;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_tolerance_set_minus(design_tolerance_s *t, double minus)
{
    // Sanity check parameters.
  assert(t);
  t->minus = minus;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_tolerance_get_minus(design_tolerance_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->minus;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_tolerance_set_precision(design_tolerance_s *t, int precision)
{
    // Sanity check parameters.
  assert(t);
  t->precision = precision;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int design_tolerance_get_precision(design_tolerance_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->precision;
}

