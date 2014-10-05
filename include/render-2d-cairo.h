#ifndef RENDER2_H
#define RENDER2_H

#include <cairo.h>

#include "drawing.h"

cairo_surface_t *render_2d_cairo(drawing_s *d);
void get_surface_size(cairo_surface_t *surface, cairo_rectangle_t *rect);

#endif // RENDER2_H
