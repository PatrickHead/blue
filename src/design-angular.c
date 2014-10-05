#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-defaults.h"

#include "design-angular.h"

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

  return angular;
}

void design_angular_destroy(design_angular_s *a)
{
  assert(a);
  if (a->alpha) vertex_destroy(a->alpha);
  if (a->beta) vertex_destroy(a->beta);
  if (a->gamma) vertex_destroy(a->gamma);
  free(a);
}

design_angular_s *design_angular_copy(design_angular_s *a)
{
  design_angular_s *na;

  assert(a);

  na = design_angular_create();
  memcpy(na, a, sizeof(design_angular_s));

  if (a->alpha) na->alpha = vertex_copy(a->alpha);
  if (a->beta) na->beta = vertex_copy(a->beta);
  if (a->gamma) na->gamma = vertex_copy(a->gamma);

  return na;
}

void design_angular_set(design_angular_s *a,
                        double angle,
                        vertex_s *alpha,
                        vertex_s *beta,
                        vertex_s *gamma,
                        double gap,
                        double extension)
{
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

void design_angular_get(design_angular_s *a,
                        double *angle,
                        vertex_s **alpha,
                        vertex_s **beta,
                        vertex_s **gamma,
                        double *gap,
                        double *extension)
{
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

void design_angular_set_angle(design_angular_s *a, double angle)
{
  assert(a);
  a->angle = angle;
}

double design_angular_get_angle(design_angular_s *a)
{
  assert(a);
  return a->angle;
}

void design_angular_set_alpha(design_angular_s *a, vertex_s *alpha)
{
  assert(a);
  assert(alpha);
  if (a->alpha) vertex_destroy(a->alpha);
  a->alpha = alpha;
  vertex_set_tag(a->alpha, "alpha");
}

vertex_s *design_angular_get_alpha(design_angular_s *a)
{
  assert(a);
  return a->alpha;
}

void design_angular_set_beta(design_angular_s *a, vertex_s *beta)
{
  assert(a);
  assert(beta);
  if (a->beta) vertex_destroy(a->beta);
  a->beta = beta;
  vertex_set_tag(a->beta, "beta");
}

vertex_s *design_angular_get_beta(design_angular_s *a)
{
  assert(a);
  return a->beta;
}

void design_angular_set_gamma(design_angular_s *a, vertex_s *gamma)
{
  assert(a);
  assert(gamma);
  if (a->gamma) vertex_destroy(a->gamma);
  a->gamma = gamma;
  vertex_set_tag(a->gamma, "gamma");
}

vertex_s *design_angular_get_gamma(design_angular_s *a)
{
  assert(a);
  return a->gamma;
}

void design_angular_set_gap(design_angular_s *a, double gap)
{
  assert(a);
  a->gap = gap;
}

double design_angular_get_gap(design_angular_s *a)
{
  assert(a);
  return a->gap;
}

void design_angular_set_extension(design_angular_s *a, double extension)
{
  assert(a);
  a->extension = extension;
}

double design_angular_get_extension(design_angular_s *a)
{
  assert(a);
  return a->extension;
}

