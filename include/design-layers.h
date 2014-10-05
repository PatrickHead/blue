#ifndef DESIGN_LAYERS_H
#define DESIGN_LAYERS_H

#include "list.h"
#include "design-layer.h"

typedef struct
{
  list_s *layers;
} design_layers_s;

design_layers_s *design_layers_create(void);
void design_layers_destroy(design_layers_s *ls);
design_layers_s *design_layers_copy(design_layers_s *ls);
void design_layers_add_layer(design_layers_s *ls, design_layer_s *l);
void design_layers_delete_layer(design_layers_s *ls, int id);
design_layer_s *design_layers_get_layer_by_id(design_layers_s *ls, int id);
design_layer_s *design_layers_get_layer_by_name(design_layers_s *ls, char *name);

#endif // DESIGN_LAYERS_H
