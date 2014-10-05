#ifndef DESIGN_TEXT_H
#define DESIGN_TEXT_H

#include "vertex.h"

#include "design-text-type.h"
#include "design-anchor-location-type.h"

typedef struct
{
  design_text_t type;
  vertex_s *location;
  double rotation;
  design_anchor_location_t anchor_point;
  double size;
  char *text;
} design_text_s;

design_text_s *design_text_create(void);
void design_text_destroy(design_text_s *t);
design_text_s *design_text_copy(design_text_s *t);

void design_text_set(design_text_s *t,
                     design_text_t type,
                     vertex_s *location,
                     double rotation,
                     design_anchor_location_t anchor_point,
                     double size,
                     char *text);
void design_text_get(design_text_s *t,
                     design_text_t *type,
                     vertex_s **location,
                     double *rotation,
                     design_anchor_location_t *anchor_point,
                     double *size,
                     char **text);

void design_text_set_type(design_text_s *t, design_text_t type); 
design_text_t design_text_get_type(design_text_s *t);
void design_text_set_location(design_text_s *t, vertex_s *location); 
vertex_s *design_text_get_location(design_text_s *t);
void design_text_set_rotation(design_text_s *t, double rotation); 
double design_text_get_rotation(design_text_s *t);
void design_text_set_anchor_point(design_text_s *t,
                                  design_anchor_location_t anchor_point); 
design_anchor_location_t design_text_get_anchor_point(design_text_s *t);
void design_text_set_size(design_text_s *t, double size); 
double design_text_get_size(design_text_s *t);
void design_text_set_text(design_text_s *t, char *text); 
char *design_text_get_text(design_text_s *t);

#endif // DESIGN_TEXT_H
