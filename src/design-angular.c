/*!
    @file design-angular.c

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

    @file design-angular.c

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

#include "design-angular.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_angular_s *design_angular_create(void)
{
  design_angular_s *angular;
  design_defaults_s *d;

  angular = (design_angular_s *)malloc(sizeof(design_angular_s));
  memset(angular, 0, sizeof(design_angular_s));

  d = design_defaults_current();
  if (d)
  {
    angular->gap = d->angular_gap;
    angular->extension = d->angular_extension;
  }

  angular->alpha = vertex_create();
  if (angular->alpha) vertex_set(angular->alpha, "alpha", 0.0, 0.0, 0.0);

  angular->beta = vertex_create();
  if (angular->beta) vertex_set(angular->beta, "beta", 0.0, 0.0, 0.0);

  angular->gamma = vertex_create();
  if (angular->gamma) vertex_set(angular->gamma, "gamma", 0.0, 0.0, 0.0);

    // Return RETVAL
  return angular;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_destroy(design_angular_s *a)
{
    // Sanity check parameters.
  assert(a);
  if (a->alpha) vertex_destroy(a->alpha);
  if (a->beta) vertex_destroy(a->beta);
  if (a->gamma) vertex_destroy(a->gamma);
  free(a);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_angular_s *design_angular_copy(design_angular_s *a)
{
  design_angular_s *na;

    // Sanity check parameters.
  assert(a);

  na = design_angular_create();
  memcpy(na, a, sizeof(design_angular_s));

  if (a->alpha) na->alpha = vertex_copy(a->alpha);
  if (a->beta) na->beta = vertex_copy(a->beta);
  if (a->gamma) na->gamma = vertex_copy(a->gamma);

    // Return RETVAL
  return na;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_set(design_angular_s *a,
                        double angle,
                        vertex_s *alpha,
                        vertex_s *beta,
                        vertex_s *gamma,
                        double gap,
                        double extension)
{
    // Sanity check parameters.
  assert(a);
  assert(alpha);
  assert(beta);
  assert(gamma);

  design_angular_set_angle(a, angle);
  design_angular_set_alpha(a, alpha);
  design_angular_set_beta(a, beta);
  design_angular_set_gamma(a, gamma);
  design_angular_set_gap(a, gap);
  design_angular_set_extension(a, extension);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_get(design_angular_s *a,
                        double *angle,
                        vertex_s **alpha,
                        vertex_s **beta,
                        vertex_s **gamma,
                        double *gap,
                        double *extension)
{
    // Sanity check parameters.
  assert(a);
  assert(angle);
  assert(alpha);
  assert(beta);
  assert(gamma);
  assert(gap);
  assert(extension);

  *angle = design_angular_get_angle(a);
  *alpha = design_angular_get_alpha(a);
  *beta = design_angular_get_beta(a);
  *gamma = design_angular_get_gamma(a);
  *gap = design_angular_get_gap(a);
  *extension = design_angular_get_extension(a);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_set_angle(design_angular_s *a, double angle)
{
    // Sanity check parameters.
  assert(a);
  a->angle = angle;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_angular_get_angle(design_angular_s *a)
{
    // Sanity check parameters.
  assert(a);
    // Return RETVAL
  return a->angle;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_set_alpha(design_angular_s *a, vertex_s *alpha)
{
    // Sanity check parameters.
  assert(a);
  assert(alpha);
  if (a->alpha) vertex_destroy(a->alpha);
  a->alpha = alpha;
  vertex_set_tag(a->alpha, "alpha");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_angular_get_alpha(design_angular_s *a)
{
    // Sanity check parameters.
  assert(a);
    // Return RETVAL
  return a->alpha;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_set_beta(design_angular_s *a, vertex_s *beta)
{
    // Sanity check parameters.
  assert(a);
  assert(beta);
  if (a->beta) vertex_destroy(a->beta);
  a->beta = beta;
  vertex_set_tag(a->beta, "beta");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_angular_get_beta(design_angular_s *a)
{
    // Sanity check parameters.
  assert(a);
    // Return RETVAL
  return a->beta;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_set_gamma(design_angular_s *a, vertex_s *gamma)
{
    // Sanity check parameters.
  assert(a);
  assert(gamma);
  if (a->gamma) vertex_destroy(a->gamma);
  a->gamma = gamma;
  vertex_set_tag(a->gamma, "gamma");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_angular_get_gamma(design_angular_s *a)
{
    // Sanity check parameters.
  assert(a);
    // Return RETVAL
  return a->gamma;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_set_gap(design_angular_s *a, double gap)
{
    // Sanity check parameters.
  assert(a);
  a->gap = gap;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_angular_get_gap(design_angular_s *a)
{
    // Sanity check parameters.
  assert(a);
    // Return RETVAL
  return a->gap;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_angular_set_extension(design_angular_s *a, double extension)
{
    // Sanity check parameters.
  assert(a);
  a->extension = extension;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_angular_get_extension(design_angular_s *a)
{
    // Sanity check parameters.
  assert(a);
    // Return RETVAL
  return a->extension;
}

