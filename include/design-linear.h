#ifndef DESIGN_LINEAR_H
#define DESIGN_LINEAR_H

#include "vertex.h"

typedef struct
{
  vertex_s *start;
  vertex_s *end;
  double gap;
  double extension_above;
  double extension_below;
  double dimension; // 0 is automatic
} design_linear_s;

design_linear_s *design_linear_create(void);
void design_linear_destroy(design_linear_s *l);
design_linear_s *design_linear_copy(design_linear_s *l);

void design_linear_set(design_linear_s *l,
                       vertex_s *start,
                       vertex_s *end,
                       double gap,
                       double extension_above,
                       double extension_below,
                       double dimension);
void design_linear_get(design_linear_s *l,
                       vertex_s **start,
                       vertex_s **end,
                       double *gap,
                       double *extension_above,
                       double *extension_below,
                       double *dimension);

void design_linear_set_start(design_linear_s *l, vertex_s *start); 
vertex_s *design_linear_get_start(design_linear_s *l);
void design_linear_set_end(design_linear_s *l, vertex_s *end); 
vertex_s *design_linear_get_end(design_linear_s *l);
void design_linear_set_gap(design_linear_s *l, double gap); 
double design_linear_get_gap(design_linear_s *l);
void design_linear_set_extension_above(design_linear_s *l,
                                       double extension_above); 
double design_linear_get_extension_above(design_linear_s *l);
void design_linear_set_extension_below(design_linear_s *l,
                                       double extension_below); 
double design_linear_get_extension_below(design_linear_s *l);
void design_linear_set_dimension(design_linear_s *l, double dimension); 
double design_linear_get_dimension(design_linear_s *l);

#endif // DESIGN_LINEAR_H
