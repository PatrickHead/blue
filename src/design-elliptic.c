#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-elliptic.h"

design_elliptic_s *design_elliptic_create(void)
{
  design_elliptic_s *elliptic;

  elliptic = (design_elliptic_s *)malloc(sizeof(design_elliptic_s));
  memset(elliptic, 0, sizeof(design_elliptic_s));

  elliptic->center = vertex_create();
  if (elliptic->center) vertex_set(elliptic->center, "center", 0.0, 0.0, 0.0);

  return elliptic;
}

void design_elliptic_destroy(design_elliptic_s *e)
{
  assert(e);
  if (e->center) vertex_destroy(e->center);
  free(e);
}

design_elliptic_s *design_elliptic_copy(design_elliptic_s *e)
{
  design_elliptic_s *ne;

  assert(e);

  ne = design_elliptic_create();
  memcpy(ne, e, sizeof(design_elliptic_s));

  if (e->center) ne->center = vertex_copy(e->center);

  return ne;
}

void design_elliptic_set(design_elliptic_s *e,
                         vertex_s *center,
                         double width,
                         double height,
                         double rotation,
                         double start_angle,
                         double end_angle)
{
  assert(e);
  assert(center);

  design_elliptic_set_center(e, center);
  design_elliptic_set_width(e, width);
  design_elliptic_set_height(e, height);
  design_elliptic_set_rotation(e, rotation);
  design_elliptic_set_start_angle(e, start_angle);
  design_elliptic_set_end_angle(e, end_angle);
}

void design_elliptic_get(design_elliptic_s *e,
                         vertex_s **center,
                         double *width,
                         double *height,
                         double *rotation,
                         double *start_angle,
                         double *end_angle)
{
  assert(e);
  assert(center);
  assert(width);
  assert(height);
  assert(rotation);
  assert(start_angle);
  assert(end_angle);

  *center = design_elliptic_get_center(e);
  *width = design_elliptic_get_width(e);
  *height = design_elliptic_get_height(e);
  *rotation = design_elliptic_get_rotation(e);
  *start_angle = design_elliptic_get_start_angle(e);
  *end_angle = design_elliptic_get_end_angle(e);
}

void design_elliptic_set_center(design_elliptic_s *e, vertex_s *center)
{
  assert(e);
  assert(center);
  if (e->center) vertex_destroy(e->center);
  e->center = center;
  vertex_set_tag(e->center, "center");
}

vertex_s *design_elliptic_get_center(design_elliptic_s *e)
{
  assert(e);
  return e->center;
}

void design_elliptic_set_width(design_elliptic_s *e, double width)
{
  assert(e);
  e->width = width;
}

double design_elliptic_get_width(design_elliptic_s *e)
{
  assert(e);
  return e->width;
}

void design_elliptic_set_height(design_elliptic_s *e, double height)
{
  assert(e);
  e->height = height;
}

double design_elliptic_get_height(design_elliptic_s *e)
{
  assert(e);
  return e->height;
}

void design_elliptic_set_rotation(design_elliptic_s *e, double rotation)
{
  assert(e);
  e->rotation = rotation;
}

double design_elliptic_get_rotation(design_elliptic_s *e)
{
  assert(e);
  return e->rotation;
}

void design_elliptic_set_start_angle(design_elliptic_s *e, double start_angle)
{
  assert(e);
  e->start_angle = start_angle;
}

double design_elliptic_get_start_angle(design_elliptic_s *e)
{
  assert(e);
  return e->start_angle;
}

void design_elliptic_set_end_angle(design_elliptic_s *e, double end_angle)
{
  assert(e);
  e->end_angle = end_angle;
}

double design_elliptic_get_end_angle(design_elliptic_s *e)
{
  assert(e);
  return e->end_angle;
}

