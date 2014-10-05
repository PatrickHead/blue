#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"
#include "reference.h"

#include "blue.h"

#include "design-elements.h"
#include "design-layer.h"

design_layer_s *design_layer_create(void)
{
  design_layer_s *layer;

  layer = (design_layer_s *)malloc(sizeof(design_layer_s));
  memset(layer, 0, sizeof(design_layer_s));

  layer->id = reference_new(BLUE_REFERENCE);
  layer->defaults = design_defaults_create();
  layer->elements = design_elements_create();

  return layer;
}

void design_layer_destroy_void(void *l)
{
  design_layer_destroy((design_layer_s *)l);
}

void design_layer_destroy(design_layer_s *l)
{
  assert(l);

  if (l->name) free(l->name);
  if (l->elements) design_elements_destroy(l->elements);
  if (l->defaults) design_defaults_destroy(l->defaults);
  free(l);
}

design_layer_s *design_layer_copy(design_layer_s *l)
{
  design_layer_s *nl;

  assert(l);

  nl = design_layer_create();
  memcpy(nl, l, sizeof(design_layer_s));

  if (l->elements)
    nl->elements = design_elements_copy(l->elements);

  return nl;
}

void design_layer_set(design_layer_s *l,
                      int id,
                      char *name,
                      design_visibility_t visibility,
                      design_defaults_s *defaults,
                      design_elements_s *elements)
{
  assert(l);
  assert(name);
  assert(defaults);
  assert(elements);

  design_layer_set_id(l, id);
  design_layer_set_name(l, name);
  design_layer_set_visibility(l, visibility);
  design_layer_set_defaults(l, defaults);
  design_layer_set_elements(l, elements);
}

void design_layer_get(design_layer_s *l,
                      int *id,
                      char **name,
                      design_visibility_t *visibility,
                      design_defaults_s **defaults,
                      design_elements_s **elements)
{
  assert(l);
  assert(id);
  assert(name);
  assert(visibility);
  assert(defaults);
  assert(elements);

  *id = design_layer_get_id(l);
  *name = design_layer_get_name(l);
  *visibility = design_layer_get_visibility(l);
  *defaults = design_layer_get_defaults(l);
  *elements = design_layer_get_elements(l);
}

void design_layer_set_id(design_layer_s *l, int id)
{
  assert(l);
  l->id = id;
}

int design_layer_get_id(design_layer_s *l)
{
  assert(l);
  return l->id;
}

void design_layer_set_name(design_layer_s *l, char *name)
{
  assert(l);
  assert(name);

  if (l->name) free(l->name);
  l->name = strdup(name);
}

char *design_layer_get_name(design_layer_s *l)
{
  assert(l);
  return l->name;
}

void design_layer_set_visibility(design_layer_s *l,
                                 design_visibility_t visibility)
{
  assert(l);

  l->visibility = visibility;
}

design_visibility_t design_layer_get_visibility(design_layer_s *l)
{
  assert(l);

  return l->visibility;
}

void design_layer_set_elements(design_layer_s *l, design_elements_s *es)
{
  assert(l);
  assert(es);

  if (l->elements) design_elements_destroy(l->elements);
  l->elements = design_elements_copy(es);
}

design_elements_s *design_layer_get_elements(design_layer_s *l)
{
  assert(l);
  return l->elements;
}

void design_layer_set_defaults(design_layer_s *l, design_defaults_s *d)
{
  assert(l);
  assert(d);

  if (l->defaults) design_defaults_destroy(l->defaults);
  l->defaults = design_defaults_copy(d);
}

design_defaults_s *design_layer_get_defaults(design_layer_s *l)
{
  assert(l);
  return l->defaults;
}

