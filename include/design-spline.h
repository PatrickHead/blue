#ifndef DESIGN_SPLINE_H
#define DESIGN_SPLINE_H

#include "vertices.h"

typedef struct
{
  vertices_s *vertices;
} design_spline_s;

design_spline_s *design_spline_create(void);
void design_spline_destroy(design_spline_s *s);
design_spline_s *design_spline_copy(design_spline_s *s);

void design_spline_set(design_spline_s *s, vertices_s *vertices);
void design_spline_get(design_spline_s *s, vertices_s **vertices);

void design_spline_set_vertices(design_spline_s *s, vertices_s *vertices);
vertices_s *design_spline_get_vertices(design_spline_s *s);

#endif // DESIGN_SPLINE_H
