#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "border.h"

border_s *border_create(void)
{
  border_s *b;

  b = (border_s *)malloc(sizeof(border_s));
  memset(b, 0, sizeof(border_s));

  b->units = units_type_mm;
  b->line_width = 1.0;
  b->margins = margins_create();

  b->background_color = color_create();
  color_set_tag(b->background_color, "background-color");
  color_white(b->background_color);

  b->line_color = color_create();
  color_set_tag(b->line_color, "line-color");
  color_black(b->line_color);

  return b;
}

void border_destroy(border_s *b)
{
  assert(b);
  if (b->margins) margins_destroy(b->margins);
  if (b->background_color) color_destroy(b->background_color);
  if (b->line_color) color_destroy(b->line_color);
  free(b);
}

border_s *border_copy(border_s *b)
{
  border_s *nb;

  assert(b);

  nb = border_create();
  memcpy(nb, b, sizeof(border_s));

  if (b->margins) nb->margins = margins_copy(b->margins);
  if (b->background_color) nb->background_color = color_copy(b->background_color);
  if (b->line_color) nb->line_color = color_copy(b->line_color);

  return nb;
}

void border_set(border_s *b,
                units_t units,
                double line_width,
                margins_s *margins,
                color_s *background_color,
                color_s *line_color)
{
  assert(b);
  assert(margins);
  assert(background_color);
  assert(line_color);

  border_set_units(b, units);
  border_set_line_width(b, line_width);
  border_set_margins(b, margins);
  border_set_background_color(b, background_color);
  border_set_line_color(b, line_color);
}

void border_get(border_s *b,
                units_t *units,
                double *line_width,
                margins_s **margins,
                color_s **background_color,
                color_s **line_color)
{
  assert(b);
  assert(units);
  assert(line_width);
  assert(margins);
  assert(background_color);
  assert(line_color);

  *units = border_get_units(b);
  *line_width = border_get_line_width(b);
  *margins = border_get_margins(b);
  *background_color = border_get_background_color(b);
  *line_color = border_get_line_color(b);
}

void border_set_units(border_s *b, units_t ut)
{
  units_t old_ut;

  assert(b);

  old_ut = b->units;
  b->units = ut;
  b->line_width = units_convert(b->line_width, old_ut, b->units);
  if (b->margins->units == old_ut)
    margins_set_units(b->margins, ut);
}

units_t border_get_units(border_s *b)
{
  assert(b);
  return b->units;
}

void border_set_line_width(border_s *b, double lw)
{
  assert(b);
  b->line_width = lw;
}

double border_get_line_width(border_s *b)
{
  assert(b);
  return b->line_width;
}

void border_set_margins(border_s *b, margins_s *m)
{
  assert(b);
  assert(m);
  if (b->margins) margins_destroy(b->margins);
  b->margins = m;
}

margins_s *border_get_margins(border_s *b)
{
  assert(b);
  return b->margins;
}

void border_set_background_color(border_s *b, color_s *background_color)
{
  assert(b);
  assert(background_color);
  if (b->background_color) color_destroy(b->background_color);
  b->background_color = background_color;
  color_set_tag(b->background_color, "background-color");
}

color_s *border_get_background_color(border_s *b)
{
  assert(b);
  return b->background_color;
}

void border_set_line_color(border_s *b, color_s *line_color)
{
  assert(b);
  assert(line_color);
  if (b->line_color) color_destroy(b->line_color);
  b->line_color = line_color;
  color_set_tag(b->line_color, "line-color");
}

color_s *border_get_line_color(border_s *b)
{
  assert(b);
  return b->line_color;
}

