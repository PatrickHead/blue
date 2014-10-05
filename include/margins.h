#ifndef MARGINS_H
#define MARGINS_H

#include "units.h"

typedef struct
{
  units_t units;
  double left;
  double right;
  double top;
  double bottom;
} margins_s;

margins_s *margins_create(void);
void margins_destroy(margins_s *m);
margins_s *margins_copy(margins_s *m);

void margins_set(margins_s *m,
                 units_t units,
                 double left,
                 double right,
                 double top,
                 double bottom);
void margins_get(margins_s *m,
                 units_t *units,
                 double *left,
                 double *right,
                 double *top,
                 double *bottom);

void margins_set_units(margins_s *m, units_t u);
units_t margins_get_units(margins_s *m);

void margins_set_left(margins_s *m, double l);
double margins_get_left(margins_s *m);

void margins_set_right(margins_s *m, double r);
double margins_get_right(margins_s *m);

void margins_set_top(margins_s *m, double t);
double margins_get_top(margins_s *m);

void margins_set_bottom(margins_s *m, double b);
double margins_get_bottom(margins_s *m);

#endif // MARGINS_H
