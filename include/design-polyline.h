#ifndef DESIGN_POLYLINE_H
#define DESIGN_POLYLINE_H

#include "vertices.h"

typedef struct
{
  vertices_s *vertices;
} design_polyline_s;

design_polyline_s *design_polyline_create(void);
void design_polyline_destroy(design_polyline_s *pl);
design_polyline_s *design_polyline_copy(design_polyline_s *el);

void design_polyline_set(design_polyline_s *pl, vertices_s *vertices);
void design_polyline_get(design_polyline_s *pl, vertices_s **vertices);

void design_polyline_set_vertices(design_polyline_s *pl, vertices_s *vertices);
vertices_s *design_polyline_get_vertices(design_polyline_s *pl);

#endif // DESIGN_POLYLINE_H
