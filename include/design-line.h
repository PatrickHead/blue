#ifndef DESIGN_VERTEX_H
#define DESIGN_VERTEX_H

#include "vertex.h"

typedef struct
{
  vertex_s *start;
  vertex_s *end;
} design_line_s;

design_line_s *design_line_create(void);
void design_line_destroy(design_line_s *l);
design_line_s *design_line_copy(design_line_s *l);

void design_line_set(design_line_s *l,
                     vertex_s *start,
                     vertex_s *end);
void design_line_get(design_line_s *l,
                     vertex_s **start,
                     vertex_s **end);

void design_line_set_start(design_line_s *l, vertex_s *start); 
vertex_s *design_line_get_start(design_line_s *l);
void design_line_set_end(design_line_s *l, vertex_s *end); 
vertex_s *design_line_get_end(design_line_s *l);

#endif // DESIGN_VERTEX_H
