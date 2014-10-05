#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-polyline.h"

design_polyline_s *design_polyline_create(void)
{
  design_polyline_s *polyline;

  polyline = (design_polyline_s *)malloc(sizeof(design_polyline_s));
  memset(polyline, 0, sizeof(design_polyline_s));

  polyline->vertices = vertices_create();

  return polyline;
}

void design_polyline_destroy(design_polyline_s *pl)
{
  assert(pl);
  if (pl->vertices) vertices_destroy(pl->vertices);
  free(pl);
}

design_polyline_s *design_polyline_copy(design_polyline_s *pl)
{
  design_polyline_s *npl;

  assert(pl);

  npl = design_polyline_create();
  memcpy(npl, pl, sizeof(design_polyline_s));

  if (pl->vertices) npl->vertices = vertices_copy(pl->vertices);

  return npl;
}

void design_polyline_set(design_polyline_s *pl, vertices_s *vertices)
{
  assert(pl);
  assert(vertices);

  design_polyline_set_vertices(pl, vertices);
}

void design_polyline_get(design_polyline_s *pl, vertices_s **vertices)
{
  assert(pl);
  assert(vertices);

  *vertices = design_polyline_get_vertices(pl);
}

void design_polyline_set_vertices(design_polyline_s *pl, vertices_s *vertices)
{
  assert(pl);
  assert(vertices);
  if (pl->vertices) vertices_destroy(pl->vertices);
  pl->vertices = vertices;
}

vertices_s *design_polyline_get_vertices(design_polyline_s *pl)
{
  assert(pl);
  return pl->vertices;
}

