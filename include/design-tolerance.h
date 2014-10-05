#ifndef DESIGN_TOLERANCE_H
#define DESIGN_TOLERANCE_H

#include "vertex.h"

typedef struct
{
  vertex_s *location;
  double text_size;
  double plus;
  double minus;
  int precision;
} design_tolerance_s;

design_tolerance_s *design_tolerance_create(void);
void design_tolerance_destroy(design_tolerance_s *t);
design_tolerance_s *design_tolerance_copy(design_tolerance_s *t);

void design_tolerance_set(design_tolerance_s *t,
                          vertex_s *location,
                          double text_size,
                          double plus,
                          double minus,
                          int precision);
void design_tolerance_get(design_tolerance_s *t,
                          vertex_s **location,
                          double *text_size,
                          double *plus,
                          double *minus,
                          int *precision);

void design_tolerance_set_location(design_tolerance_s *t, vertex_s *location); 
vertex_s *design_tolerance_get_location(design_tolerance_s *t);

void design_tolerance_set_text_size(design_tolerance_s *t, double text_size); 
double design_tolerance_get_text_size(design_tolerance_s *t);

void design_tolerance_set_plus(design_tolerance_s *t, double plus); 
double design_tolerance_get_plus(design_tolerance_s *t);

void design_tolerance_set_minus(design_tolerance_s *t, double minus); 
double design_tolerance_get_minus(design_tolerance_s *t);

void design_tolerance_set_precision(design_tolerance_s *t, int precision); 
int design_tolerance_get_precision(design_tolerance_s *t);

#endif // DESIGN_TOLERANCE_H
