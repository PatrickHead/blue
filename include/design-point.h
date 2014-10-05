#ifndef DESIGN_POINT_H
#define DESIGN_POINT_H

#include "vertex.h"

typedef struct
{
  vertex_s *location;
} design_point_s;

design_point_s *design_point_create(void);
void design_point_destroy(design_point_s *p);
design_point_s *design_point_copy(design_point_s *p);

void design_point_set(design_point_s *p,
                      vertex_s *location);
void design_point_get(design_point_s *p,
                      vertex_s **location);

void design_point_set_location(design_point_s *p, vertex_s *location); 
vertex_s *design_point_get_location(design_point_s *p);

#endif // DESIGN_POINT_H
