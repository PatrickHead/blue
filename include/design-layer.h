#ifndef DESIGN_LAYER_H
#define DESIGN_LAYER_H

#include "design-defaults.h"
#include "design-visibility-type.h"
#include "design-elements.h"

typedef struct
{
  int id;
  char *name;
  design_visibility_t visibility;
  design_defaults_s *defaults;
  design_elements_s *elements;
} design_layer_s;

design_layer_s *design_layer_create(void);
void design_layer_destroy_void(void *l);
void design_layer_destroy(design_layer_s *l);
design_layer_s *design_layer_copy(design_layer_s *l);

void design_layer_set(design_layer_s *l,
                      int id,
                      char *name,
                      design_visibility_t visibility,
                      design_defaults_s *defaults,
                      design_elements_s *elements);
void design_layer_get(design_layer_s *l,
                      int *id,
                      char **name,
                      design_visibility_t *visibility,
                      design_defaults_s **defaults,
                      design_elements_s **elements);

void design_layer_set_id(design_layer_s *l, int id);
int design_layer_get_id(design_layer_s *l);

void design_layer_set_name(design_layer_s *l, char *name);
char *design_layer_get_name(design_layer_s *l);

void design_layer_set_visibility(design_layer_s *l,
                                 design_visibility_t visibility);
design_visibility_t design_layer_get_visibility(design_layer_s *l);

void design_layer_set_defaults(design_layer_s *l, design_defaults_s *d);
design_defaults_s *design_layer_get_defaults(design_layer_s *l);

void design_layer_set_elements(design_layer_s *l, design_elements_s *es);
design_elements_s *design_layer_get_elements(design_layer_s *l);

#endif // DESIGN_LAYER_H
