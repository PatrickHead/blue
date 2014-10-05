#ifndef DESIGN_ELEMENTS_H
#define DESIGN_ELEMENTS_H

#include "list.h"
#include "design-element.h"

typedef struct
{
  list_s *elements;
} design_elements_s;

design_elements_s *design_elements_create(void);
void design_elements_destroy(design_elements_s *es);
design_elements_s *design_elements_copy(design_elements_s *es);
void design_elements_add_element(design_elements_s *es, design_element_s *e);
void design_elements_delete_element(design_elements_s *es, int id);
design_element_s *design_elements_get_element_by_id(design_elements_s *ls,
                                                    int id);

#endif // DESIGN_ELEMENTS_H
