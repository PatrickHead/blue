#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-radial.h"

design_radial_s *design_radial_create(void)
{
  design_radial_s *radial;

  radial = (design_radial_s *)malloc(sizeof(design_radial_s));
  memset(radial, 0, sizeof(design_radial_s));

  radial->center = vertex_create();
  if (radial->center) vertex_set(radial->center, "center", 0.0, 0.0, 0.0);

  return radial;
}

void design_radial_destroy(design_radial_s *r)
{
  assert(r);
  if (r->center) vertex_destroy(r->center);
  free(r);
}

design_radial_s *design_radial_copy(design_radial_s *r)
{
  design_radial_s *nr;

  assert(r);

  nr = design_radial_create();
  memcpy(nr, r, sizeof(design_radial_s));

  if (r->center) nr->center = vertex_copy(r->center);

  return nr;
}

void design_radial_set(design_radial_s *r,
                       design_radial_t type,
                       vertex_s *center,
                       double major,
                       double minor,
                       double angle,
                       double leader)
{
  assert(r);
  assert(center);

  design_radial_set_type(r, type);
  design_radial_set_center(r, center);
  design_radial_set_major(r, major);
  design_radial_set_minor(r, minor);
  design_radial_set_angle(r, angle);
  design_radial_set_leader(r, type);
}

void design_radial_get(design_radial_s *r,
                       design_radial_t *type,
                       vertex_s **center,
                       double *major,
                       double *minor,
                       double *angle,
                       double *leader)
{
  assert(r);
  assert(type);
  assert(center);
  assert(major);
  assert(minor);
  assert(angle);
  assert(leader);

  *type = design_radial_get_type(r);
  *center = design_radial_get_center(r);
  *major = design_radial_get_major(r);
  *minor = design_radial_get_minor(r);
  *angle = design_radial_get_angle(r);
  *leader = design_radial_get_leader(r);
}

void design_radial_set_type(design_radial_s *r, design_radial_t type)
{
  assert(r);
  r->type = type;
}

design_radial_t design_radial_get_type(design_radial_s *r)
{
  assert(r);
  return r->type;
}

void design_radial_set_center(design_radial_s *r, vertex_s *center)
{
  assert(r);
  if (r->center) vertex_destroy(r->center);
  r->center = center;
  vertex_set_tag(r->center, "center");
}

vertex_s *design_radial_get_center(design_radial_s *r)
{
  assert(r);
  return r->center;
}

void design_radial_set_major(design_radial_s *r, double major)
{
  assert(r);
  r->major = major;
}

double design_radial_get_major(design_radial_s *r)
{
  assert(r);
  return r->major;
}

void design_radial_set_minor(design_radial_s *r, double minor)
{
  assert(r);
  r->minor = minor;
}

double design_radial_get_minor(design_radial_s *r)
{
  assert(r);
  return r->minor;
}

void design_radial_set_angle(design_radial_s *r, double angle)
{
  assert(r);
  r->angle = angle;
}

double design_radial_get_angle(design_radial_s *r)
{
  assert(r);
  return r->angle;
}

void design_radial_set_leader(design_radial_s *r, double leader)
{
  assert(r);
  r->leader = leader;
}

double design_radial_get_leader(design_radial_s *r)
{
  assert(r);
  return r->leader;
}

