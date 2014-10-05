#ifndef BORDER_H
#define BORDER_H

#include "units.h"
#include "margins.h"
#include "color.h"

typedef struct
{
  units_t units;
  double line_width;
  margins_s *margins;
  color_s *background_color;
  color_s *line_color;
} border_s;

border_s *border_create(void);
void border_destroy(border_s *b);
border_s *border_copy(border_s *b);

void border_set(border_s *b,
                units_t units,
                double line_width,
                margins_s *margins,
                color_s *background_color,
                color_s *line_color);
void border_get(border_s *b,
                units_t *units,
                double *line_width,
                margins_s **margins,
                color_s **background_color,
                color_s **line_color);

void border_set_units(border_s *b, units_t ut);
units_t border_get_units(border_s *b);

void border_set_line_width(border_s *b, double lw);
double border_get_line_width(border_s *b);

void border_set_margins(border_s *b, margins_s *m);
margins_s *border_get_margins(border_s *b);

void border_set_background_color(border_s *b, color_s *background_color);
color_s *border_get_background_color(border_s *b);

void border_set_line_color(border_s *b, color_s *line_color);
color_s *border_get_line_color(border_s *b);

#endif // BORDER_H

