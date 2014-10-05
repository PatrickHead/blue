#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-defaults.h"

#include "design-dimension.h"

design_dimension_s *design_dimension_create(void)
{
  design_dimension_s *dimension;

  dimension = (design_dimension_s *)malloc(sizeof(design_dimension_s));
  memset(dimension, 0, sizeof(design_dimension_s));

  dimension->text_location = vertex_create();
  if (dimension->text_location)
    vertex_set(dimension->text_location, "text-location", 0.0, 0.0, 0.0);

  design_dimension_set_type(dimension, design_dimension_type_linear);

  return dimension;
}

void design_dimension_destroy(design_dimension_s *d)
{
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

design_dimension_s *design_dimension_copy(design_dimension_s *d)
{
  design_dimension_s *nd;

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

  return nd;
}

void design_dimension_set(design_dimension_s *d,
                          design_dimension_t type,
                          double text_size,
                          vertex_s *text_location,
                          int precision,
                          void *data)
{
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

void design_dimension_get(design_dimension_s *d,
                          design_dimension_t *type,
                          double *text_size,
                          vertex_s **text_location,
                          int *precision,
                          void **data)
{
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

void design_dimension_set_type(design_dimension_s *d, design_dimension_t type)
{
  design_defaults_s *dfs;

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

design_dimension_t design_dimension_get_type(design_dimension_s *d)
{
  assert(d);
  return d->type;
}

void design_dimension_set_text_size(design_dimension_s *d, double text_size)
{
  assert(d);
  d->text_size = text_size;
}

double design_dimension_get_text_size(design_dimension_s *d)
{
  assert(d);
  return d->text_size;
}

void design_dimension_set_text_location(design_dimension_s *d,
                                        vertex_s *text_location)
{
  assert(d);
  assert(text_location);
  if (d->text_location) vertex_destroy(d->text_location);
  d->text_location = text_location;
  vertex_set_tag(d->text_location, "text-location");
}

vertex_s *design_dimension_get_text_location(design_dimension_s *d)
{
  assert(d);
  return d->text_location;
}

void design_dimension_set_precision(design_dimension_s *d, int precision)
{
  assert(d);
  d->precision = precision;
}

int design_dimension_get_precision(design_dimension_s *d)
{
  assert(d);
  return d->precision;
}

void design_dimension_set_angular(design_dimension_s *d,
                                  design_angular_s *angular)
{
  assert(d);
  assert(angular);

  design_dimension_set_type(d, design_dimension_type_angular);
  design_angular_destroy(d->angular);
  d->angular = angular;
}
 
design_angular_s *design_dimension_get_angular(design_dimension_s *d)
{
  assert(d);
  return d->angular;
}

void design_dimension_set_linear(design_dimension_s *d, design_linear_s *linear)
{
  assert(d);
  assert(linear);

  design_dimension_set_type(d, design_dimension_type_linear);
  design_linear_destroy(d->linear);
  d->linear = linear;
}
 
design_linear_s *design_dimension_get_linear(design_dimension_s *d)
{
  assert(d);
  return d->linear;
}

void design_dimension_set_radial(design_dimension_s *d, design_radial_s *radial)
{
  assert(d);
  assert(radial);

  design_dimension_set_type(d, design_dimension_type_radial);
  design_radial_destroy(d->radial);
  d->radial = radial;
}
 
design_radial_s *design_dimension_get_radial(design_dimension_s *d)
{
  assert(d);
  return d->radial;
}

