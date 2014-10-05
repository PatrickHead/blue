#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-defaults.h"

#include "design-tolerance.h"

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

  return tolerance;
}

void design_tolerance_destroy(design_tolerance_s *t)
{
  assert(t);
  if (t->location) vertex_destroy(t->location);
  free(t);
}

design_tolerance_s *design_tolerance_copy(design_tolerance_s *t)
{
  design_tolerance_s *nt;

  assert(t);

  nt = design_tolerance_create();
  memcpy(nt, t, sizeof(design_tolerance_s));

  if (t->location) nt->location = vertex_copy(t->location);

  return nt;
}

void design_tolerance_set(design_tolerance_s *t,
                          vertex_s *location,
                          double text_size,
                          double plus,
                          double minus,
                          int precision)
{
  assert(t);
  assert(location);

  design_tolerance_set_location(t, location);
  design_tolerance_set_text_size(t, text_size);
  design_tolerance_set_plus(t, plus);
  design_tolerance_set_minus(t, minus);
  design_tolerance_set_precision(t, precision);
}

void design_tolerance_get(design_tolerance_s *t,
                          vertex_s **location,
                          double *text_size,
                          double *plus,
                          double *minus,
                          int *precision)
{
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

void design_tolerance_set_location(design_tolerance_s *t, vertex_s *location)
{
  assert(t);
  assert(location);
  if (t->location) vertex_destroy(t->location);
  t->location = location;
  vertex_set_tag(t->location, "location");
}

vertex_s *design_tolerance_get_location(design_tolerance_s *t)
{
  assert(t);
  return t->location;
}

void design_tolerance_set_text_size(design_tolerance_s *t, double text_size)
{
  assert(t);
  t->text_size = text_size;
}

double design_tolerance_get_text_size(design_tolerance_s *t)
{
  assert(t);
  return t->text_size;
}

void design_tolerance_set_plus(design_tolerance_s *t, double plus)
{
  assert(t);
  t->plus = plus;
}

double design_tolerance_get_plus(design_tolerance_s *t)
{
  assert(t);
  return t->plus;
}

void design_tolerance_set_minus(design_tolerance_s *t, double minus)
{
  assert(t);
  t->minus = minus;
}

double design_tolerance_get_minus(design_tolerance_s *t)
{
  assert(t);
  return t->minus;
}

void design_tolerance_set_precision(design_tolerance_s *t, int precision)
{
  assert(t);
  t->precision = precision;
}

int design_tolerance_get_precision(design_tolerance_s *t)
{
  assert(t);
  return t->precision;
}

