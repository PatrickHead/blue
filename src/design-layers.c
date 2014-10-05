#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "design-layers.h"

design_layers_s *design_layers_create(void)
{
  design_layers_s *ls;

  ls = (design_layers_s *)malloc(sizeof(design_layers_s));
  memset(ls, 0, sizeof(design_layers_s));

  ls->layers = list_new();
  list_set_free(ls->layers, design_layer_destroy_void);

  return ls;
}

void design_layers_destroy(design_layers_s *ls)
{
  assert(ls);

  if (ls->layers) list_destroy(ls->layers);

  free(ls);
}

design_layers_s *design_layers_copy(design_layers_s *ls)
{
  design_layers_s *nls;
  design_layer_s *l;
  design_layer_s *nl;

  assert(ls);

  nls = design_layers_create();
  memcpy(nls, ls, sizeof(design_layers_s));

  if (ls->layers)
  {
    nls->layers = list_new();
    for (l = (design_layer_s *)list_head(ls->layers);
         l;
         l = (design_layer_s *)list_next(ls->layers))
    {
      nl = design_layer_copy(l);
      list_insert(nls->layers, (void *)nl, (void *)TAIL);
    }
  }

  return nls;
}

void design_layers_add_layer(design_layers_s *ls, design_layer_s *l)
{
  assert(ls);
  assert(l);
  list_insert(ls->layers, l, (void *)TAIL);
}

void design_layers_delete_layer(design_layers_s *ls, int id)
{
  design_layer_s *l;

  assert(ls);

  if (ls->layers)
  {
    for (l = (design_layer_s *)list_head(ls->layers);
         l;
         l = (design_layer_s *)list_next(ls->layers))
    {
      if (l->id == id)
      {
        list_delete(ls->layers, l);
        break;
      }
    }
  }
}

design_layer_s *design_layers_get_layer_by_id(design_layers_s *ls, int id)
{
  design_layer_s *l;

  assert(ls);

  for (l = (design_layer_s *)list_head(ls->layers);
       l;
       l = (design_layer_s *)list_next(ls->layers))
  {
    if (l->id == id)
      return l;
  }

  return NULL;
}

design_layer_s *design_layers_get_layer_by_name(design_layers_s *ls, char *name)
{
  design_layer_s *l;

  assert(ls);
  assert(name);

  for (l = (design_layer_s *)list_head(ls->layers);
       l;
       l = (design_layer_s *)list_next(ls->layers))
  {
    if (!strcmp(l->name, name))
      return l;
  }

  return NULL;
}

