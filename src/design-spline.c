#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-spline.h"

design_spline_s *design_spline_create(void)
{
  design_spline_s *spline;

  spline = (design_spline_s *)malloc(sizeof(design_spline_s));
  memset(spline, 0, sizeof(design_spline_s));

  spline->vertices = vertices_create();

  return spline;
}

void design_spline_destroy(design_spline_s *s)
{
  assert(s);
  if (s->vertices) vertices_destroy(s->vertices);
  free(s);
}

design_spline_s *design_spline_copy(design_spline_s *s)
{
  design_spline_s *ns;

  assert(s);

  ns = design_spline_create();
  memcpy(ns, s, sizeof(design_spline_s));

  if (s->vertices) ns->vertices = vertices_copy(s->vertices);

  return ns;
}

void design_spline_set(design_spline_s *s, vertices_s *vertices)
{
  assert(s);
  assert(vertices);

  design_spline_set_vertices(s, vertices);
}

void design_spline_get(design_spline_s *s, vertices_s **vertices)
{
  assert(s);
  assert(vertices);

  *vertices = design_spline_get_vertices(s);
}

void design_spline_set_vertices(design_spline_s *s, vertices_s *vertices)
{
  assert(s);
  assert(vertices);
  if (s->vertices) vertices_destroy(s->vertices);
  s->vertices = vertices;
}

vertices_s *design_spline_get_vertices(design_spline_s *s)
{
  assert(s);
  return s->vertices;
}

