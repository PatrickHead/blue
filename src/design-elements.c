#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "design-elements.h"

design_elements_s *design_elements_create(void)
{
  design_elements_s *es;

  es = (design_elements_s *)malloc(sizeof(design_elements_s));
  memset(es, 0, sizeof(design_elements_s));

  es->elements = list_create();
  list_set_free(es->elements, design_element_destroy_void);

  return es;
}

void design_elements_destroy(design_elements_s *es)
{
  assert(es);

  if (es->elements) list_destroy(es->elements);

  free(es);
}

design_elements_s *design_elements_copy(design_elements_s *es)
{
  design_elements_s *nes;
  design_element_s *e;
  design_element_s *ne;

  assert(es);

  nes = design_elements_create();
  memcpy(nes, es, sizeof(design_elements_s));

  if (es->elements)
  {
    nes->elements = list_create();
    for (e = (design_element_s *)list_head(es->elements);
         e;
         e = (design_element_s *)list_next(es->elements))
    {
      ne = design_element_copy(e);
      list_insert(nes->elements, (void *)ne, (void *)TAIL);
    }
  }

  return nes;
}

void design_elements_add_element(design_elements_s *es, design_element_s *e)
{
  assert(es);
  assert(e);
  list_insert(es->elements, e, (void *)TAIL);
}

void design_elements_delete_element(design_elements_s *es, int id)
{
  design_element_s *e;

  assert(es);

  if (es->elements)
  {
    for (e = (design_element_s *)list_head(es->elements);
         e;
         e = (design_element_s *)list_next(es->elements))
    {
      if (e->id == id)
      {
        list_delete(es->elements, e);
        break;
      }
    }
  }
}

design_element_s *design_elements_get_element_by_id(design_elements_s *es, int id)
{
  design_element_s *e;

  assert(es);

  for (e = (design_element_s *)list_head(es->elements);
       e;
       e = (design_element_s *)list_next(es->elements))
  {
    if (e->id == id)
      return e;
  }

  return NULL;
}

