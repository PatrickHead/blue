#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-text.h"

design_text_s *design_text_create(void)
{
  design_text_s *text;

  text = (design_text_s *)malloc(sizeof(design_text_s));
  memset(text, 0, sizeof(design_text_s));

  text->location = vertex_create();
  if (text->location) vertex_set(text->location, "location", 0.0, 0.0, 0.0);

  return text;
}

void design_text_destroy(design_text_s *t)
{
  assert(t);
  if (t->location) vertex_destroy(t->location);
  if (t->text) free(t->text);
  free(t);
}

design_text_s *design_text_copy(design_text_s *t)
{
  design_text_s *nt;

  assert(t);

  nt = design_text_create();
  memcpy(nt, t, sizeof(design_text_s));
  if (t->text) nt->location = vertex_copy(t->location);
  if (t->text) nt->text = strdup(t->text);

  return nt;
}

void design_text_set_type(design_text_s *t, design_text_t type)
{
  assert(t);
  t->type = type;
}

design_text_t design_text_get_type(design_text_s *t)
{
  assert(t);
  return t->type;
}

void design_text_set(design_text_s *t,
                     design_text_t type,
                     vertex_s *location,
                     double rotation,
                     design_anchor_location_t anchor_point,
                     double size,
                     char *text)
{
  assert(t);
  assert(location);
  assert(text);

  design_text_set_type(t, type);
  design_text_set_location(t, location);
  design_text_set_rotation(t, rotation);
  design_text_set_anchor_point(t, anchor_point);
  design_text_set_size(t, size);
  design_text_set_text(t, text);
}

void design_text_get(design_text_s *t,
                     design_text_t *type,
                     vertex_s **location,
                     double *rotation,
                     design_anchor_location_t *anchor_point,
                     double *size,
                     char **text)
{
  assert(t);
  assert(type);
  assert(location);
  assert(rotation);
  assert(anchor_point);
  assert(size);
  assert(text);

  *type = design_text_get_type(t);
  *location = design_text_get_location(t);
  *rotation = design_text_get_rotation(t);
  *anchor_point = design_text_get_anchor_point(t);
  *size = design_text_get_size(t);
  *text = design_text_get_text(t);
}

void design_text_set_location(design_text_s *t, vertex_s *location)
{
  assert(t);
  assert(location);
  if (t->location) vertex_destroy(t->location);
  t->location = location;
  vertex_set_tag(t->location, "location");
}

vertex_s *design_text_get_location(design_text_s *t)
{
  assert(t);
  return t->location;
}

void design_text_set_rotation(design_text_s *t, double rotation)
{
  assert(t);
  t->rotation = rotation;
}

double design_text_get_rotation(design_text_s *t)
{
  assert(t);
  return t->rotation;
}

void design_text_set_anchor_point(design_text_s *t, design_anchor_location_t anchor_point)
{
  assert(t);
  t->anchor_point = anchor_point;
}

design_anchor_location_t design_text_get_anchor_point(design_text_s *t)
{
  assert(t);
  return t->anchor_point;
}

void design_text_set_size(design_text_s *t, double size)
{
  assert(t);
  t->size = size;
}

double design_text_get_size(design_text_s *t)
{
  assert(t);
  return t->size;
}

void design_text_set_text(design_text_s *t, char * text)
{
  assert(t);
  if (t->text) free(t->text);
  t->text = strdup(text);
}

char * design_text_get_text(design_text_s *t)
{
  assert(t);
  return t->text;
}

