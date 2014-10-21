/*!
    @file design-dimension.c

    @brief SOURCE_BRIEF

    @timestamp Mon, 06 Jan 2014 15:17:36 +0000

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

    @file design-dimension.c

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

#include "design-dimension.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_dimension_s *design_dimension_create(void)
{
  design_dimension_s *dimension;

  dimension = (design_dimension_s *)malloc(sizeof(design_dimension_s));
  memset(dimension, 0, sizeof(design_dimension_s));

  dimension->text_location = vertex_create();
  if (dimension->text_location)
    vertex_set(dimension->text_location, "text-location", 0.0, 0.0, 0.0);

  design_dimension_set_type(dimension, design_dimension_type_linear);

    // Return RETVAL
  return dimension;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_destroy(design_dimension_s *d)
{
    // Sanity check parameters.
  assert(d);
  if (d->text_location) vertex_destroy(d->text_location);
  switch (d->type)
  {
    case design_dimension_type_angular:
      design_angular_destroy(d->angular);
      break;
    case design_dimension_type_linear:
      design_linear_destroy(d->linear);
      break;
    case design_dimension_type_radial:
      design_radial_destroy(d->radial);
      break;
    default: break;
  }
  free(d);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_dimension_s *design_dimension_copy(design_dimension_s *d)
{
  design_dimension_s *nd;

    // Sanity check parameters.
  assert(d);

  nd = design_dimension_create();
  memcpy(nd, d, sizeof(design_dimension_s));

  if (d->text_location) nd->text_location = vertex_copy(d->text_location);

  switch (d->type)
  {
    case design_dimension_type_angular:
      if (nd->angular) nd->angular = design_angular_copy(d->angular);
      break;
    case design_dimension_type_linear:
      if (nd->linear) nd->linear = design_linear_copy(d->linear);
      break;
    case design_dimension_type_radial:
      if (nd->radial) nd->radial = design_radial_copy(d->radial);
      break;
    default: break;
  }

    // Return RETVAL
  return nd;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_set(design_dimension_s *d,
                          design_dimension_t type,
                          double text_size,
                          vertex_s *text_location,
                          int precision,
                          void *data)
{
    // Sanity check parameters.
  assert(d);
  assert(text_location);
  assert(data);

  design_dimension_set_type(d, type);
  design_dimension_set_text_size(d, text_size);
  design_dimension_set_text_location(d, text_location);
  design_dimension_set_precision(d, precision);
  switch (d->type)
  {
    case design_dimension_type_angular:
      design_dimension_set_angular(d, (design_angular_s *)data);
      break;
    case design_dimension_type_linear:
      design_dimension_set_linear(d, (design_linear_s *)data);
      break;
    case design_dimension_type_radial:
      design_dimension_set_radial(d, (design_radial_s *)data);
      break;
    default: break;
  }
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_get(design_dimension_s *d,
                          design_dimension_t *type,
                          double *text_size,
                          vertex_s **text_location,
                          int *precision,
                          void **data)
{
    // Sanity check parameters.
  assert(d);
  assert(type);
  assert(text_size);
  assert(text_location);
  assert(precision);
  assert(data);

  *type = design_dimension_get_type(d);
  *text_size = design_dimension_get_text_size(d);
  *text_location = design_dimension_get_text_location(d);
  *precision = design_dimension_get_precision(d);
  switch (d->type)
  {
    case design_dimension_type_angular:
      *data = design_dimension_get_angular(d);
      break;
    case design_dimension_type_linear:
      *data = design_dimension_get_linear(d);
      break;
    case design_dimension_type_radial:
      *data = design_dimension_get_radial(d);
      break;
    default: break;
  }
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_set_type(design_dimension_s *d, design_dimension_t type)
{
  design_defaults_s *dfs;

    // Sanity check parameters.
  assert(d);

  dfs = design_defaults_current();

  switch (d->type)
  {
    case design_dimension_type_angular:
      if (d->angular) design_angular_destroy(d->angular);
      break;
    case design_dimension_type_linear:
      if (d->linear) design_linear_destroy(d->linear);
      break;
    case design_dimension_type_radial:
      if (d->radial) design_radial_destroy(d->radial);
      break;
    default: break;
  }

  d->type = type;

  switch (d->type)
  {
    case design_dimension_type_angular:
      d->angular = design_angular_create();
      break;
    case design_dimension_type_linear:
      d->linear = design_linear_create();
      break;
    case design_dimension_type_radial:
      d->radial = design_radial_create();
      break;
    default: break;
  }

  if (dfs)
  {
    d->text_size = dfs->dimension_text_size;
    d->precision = dfs->dimension_precision;
  }
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_dimension_t design_dimension_get_type(design_dimension_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->type;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_set_text_size(design_dimension_s *d, double text_size)
{
    // Sanity check parameters.
  assert(d);
  d->text_size = text_size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_dimension_get_text_size(design_dimension_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->text_size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_set_text_location(design_dimension_s *d,
                                        vertex_s *text_location)
{
    // Sanity check parameters.
  assert(d);
  assert(text_location);
  if (d->text_location) vertex_destroy(d->text_location);
  d->text_location = text_location;
  vertex_set_tag(d->text_location, "text-location");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_dimension_get_text_location(design_dimension_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->text_location;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_set_precision(design_dimension_s *d, int precision)
{
    // Sanity check parameters.
  assert(d);
  d->precision = precision;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int design_dimension_get_precision(design_dimension_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->precision;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_set_angular(design_dimension_s *d,
                                  design_angular_s *angular)
{
    // Sanity check parameters.
  assert(d);
  assert(angular);

  design_dimension_set_type(d, design_dimension_type_angular);
  design_angular_destroy(d->angular);
  d->angular = angular;
}
 
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_angular_s *design_dimension_get_angular(design_dimension_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->angular;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_set_linear(design_dimension_s *d, design_linear_s *linear)
{
    // Sanity check parameters.
  assert(d);
  assert(linear);

  design_dimension_set_type(d, design_dimension_type_linear);
  design_linear_destroy(d->linear);
  d->linear = linear;
}
 
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_linear_s *design_dimension_get_linear(design_dimension_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->linear;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_dimension_set_radial(design_dimension_s *d, design_radial_s *radial)
{
    // Sanity check parameters.
  assert(d);
  assert(radial);

  design_dimension_set_type(d, design_dimension_type_radial);
  design_radial_destroy(d->radial);
  d->radial = radial;
}
 
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_radial_s *design_dimension_get_radial(design_dimension_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->radial;
}

