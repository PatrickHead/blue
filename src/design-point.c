#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-point.h"

design_point_s *design_point_create(void)
{
  design_point_s *point;

  point = (design_point_s *)malloc(sizeof(design_point_s));
  memset(point, 0, sizeof(design_point_s));

  point->location = vertex_create();
  if (point->location) vertex_set(point->location, "location", 0.0, 0.0, 0.0);

  return point;
}

void design_point_destroy(design_point_s *p)
{
  assert(p);
  if (p->location) vertex_destroy(p->location);
  free(p);
}

design_point_s *design_point_copy(design_point_s *p)
{
  design_point_s *np;

  assert(p);

  np = design_point_create();
  memcpy(np, p, sizeof(design_point_s));

  if (p->location) np->location = vertex_copy(p->location);

  return np;
}

void design_point_set(design_point_s *p,
                      vertex_s *location)
{
  assert(p);
  assert(location);

  design_point_set_location(p, location);
}

void design_point_get(design_point_s *p,
                      vertex_s **location)
{
  assert(p);
  assert(location);

  *location = design_point_get_location(p);
}

void design_point_set_location(design_point_s *p, vertex_s *location)
{
  assert(p);
  assert(location);
  if (p->location) vertex_destroy(p->location);
  p->location = location;
  vertex_set_tag(p->location, "location");
}

vertex_s *design_point_get_location(design_point_s *p)
{
  assert(p);
  return p->location;
}

