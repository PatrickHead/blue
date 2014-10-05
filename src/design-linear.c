#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-defaults.h"

#include "design-linear.h"

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

  return linear;
}

void design_linear_destroy(design_linear_s *l)
{
  assert(l);
  if (l->start) vertex_destroy(l->start);
  if (l->end) vertex_destroy(l->end);
  free(l);
}

design_linear_s *design_linear_copy(design_linear_s *l)
{
  design_linear_s *nl;

  assert(l);

  nl = design_linear_create();
  memcpy(nl, l, sizeof(design_linear_s));

  if (l->start) nl->start = vertex_copy(l->start);
  if (l->end) nl->end = vertex_copy(l->end);

  return nl;
}

void design_linear_set(design_linear_s *l,
                       vertex_s *start,
                       vertex_s *end,
                       double gap,
                       double extension_above,
                       double extension_below,
                       double dimension)
{
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

void design_linear_get(design_linear_s *l,
                       vertex_s **start,
                       vertex_s **end,
                       double *gap,
                       double *extension_above,
                       double *extension_below,
                       double *dimension)
{
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

void design_linear_set_start(design_linear_s *l, vertex_s *start)
{
  assert(l);
  assert(start);
  if (l->start) vertex_destroy(l->start);
  l->start = start;
  vertex_set_tag(l->start, "start");
}

vertex_s *design_linear_get_start(design_linear_s *l)
{
  assert(l);
  return l->start;
}

void design_linear_set_end(design_linear_s *l, vertex_s *end)
{
  assert(l);
  assert(end);
  if (l->end) vertex_destroy(l->end);
  l->end = end;
  vertex_set_tag(l->end, "end");
}

vertex_s *design_linear_get_end(design_linear_s *l)
{
  assert(l);
  return l->end;
}

void design_linear_set_gap(design_linear_s *l, double gap)
{
  assert(l);
  l->gap = gap;
}

double design_linear_get_gap(design_linear_s *l)
{
  assert(l);
  return l->gap;
}

void design_linear_set_extension_above(design_linear_s *l, double extension_above)
{
  assert(l);
  l->extension_above = extension_above;
}

double design_linear_get_extension_above(design_linear_s *l)
{
  assert(l);
  return l->extension_above;
}

void design_linear_set_extension_below(design_linear_s *l, double extension_below)
{
  assert(l);
  l->extension_below = extension_below;
}

double design_linear_get_extension_below(design_linear_s *l)
{
  assert(l);
  return l->extension_below;
}

void design_linear_set_dimension(design_linear_s *l, double dimension)
{
  assert(l);
  l->dimension = dimension;
}

double design_linear_get_dimension(design_linear_s *l)
{
  assert(l);
  return l->dimension;
}

