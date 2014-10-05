#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "margins.h"

margins_s *margins_create(void)
{
  margins_s *m;
  m = (margins_s *)malloc(sizeof(margins_s));
  memset(m, 0, sizeof(margins_s));
  m->units = units_type_mm;
  m->top = m->bottom = m->left = m->right = 6.35;
  return m;
}

void margins_destroy(margins_s *m)
{
  assert(m);
  free(m);
  return;
}

margins_s *margins_copy(margins_s *m)
{
  margins_s *nm;

  assert(m);

  nm = margins_create();
  memcpy(nm, m, sizeof(margins_s));

  return nm;
}

void margins_set(margins_s *m,
                 units_t units,
                 double left,
                 double right,
                 double top,
                 double bottom)
{
  assert(m);

  margins_set_units(m, units);
  margins_set_left(m, left);
  margins_set_right(m, right);
  margins_set_top(m, top);
  margins_set_bottom(m, bottom);
}

void margins_get(margins_s *m,
                 units_t *units,
                 double *left,
                 double *right,
                 double *top,
                 double *bottom)
{
  assert(m);
  assert(units);
  assert(left);
  assert(right);
  assert(top);
  assert(bottom);

  *units = margins_get_units(m);
  *left = margins_get_left(m);
  *right = margins_get_right(m);
  *top = margins_get_top(m);
  *bottom = margins_get_bottom(m);
}

void margins_set_units(margins_s *m, units_t u)
{
  units_t old_type;

  assert(m);

  old_type = m->units;

  m->units = u;
  m->top = units_convert(m->top, old_type, m->units);
  m->bottom = units_convert(m->bottom, old_type, m->units);
  m->left = units_convert(m->left, old_type, m->units);
  m->right = units_convert(m->right, old_type, m->units);
}

units_t margins_get_units(margins_s *m)
{
  assert(m);
  return m->units;
}

void margins_set_left(margins_s *m, double l)
{
  assert(m);
  m->left = l;
}

double margins_get_left(margins_s *m)
{
  assert(m);
  return m->left;
}

void margins_set_right(margins_s *m, double r)
{
  assert(m);
  m->right = r;
}

double margins_get_right(margins_s *m)
{
  assert(m);
  return m->right;
}

void margins_set_top(margins_s *m, double t)
{
  assert(m);
  m->top = t;
}

double margins_get_top(margins_s *m)
{
  assert(m);
  return m->top;
}

void margins_set_bottom(margins_s *m, double b)
{
  assert(m);
  m->bottom = b;
}

double margins_get_bottom(margins_s *m)
{
  assert(m);
  return m->bottom;
}

