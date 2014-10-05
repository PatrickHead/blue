#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "blue.h"

#include "design-element.h"

design_element_s *design_element_create(void)
{
  design_element_s *element;

  element = (design_element_s *)malloc(sizeof(design_element_s));
  memset(element, 0, sizeof(design_element_s));

  element->id = reference_new(BLUE_REFERENCE);

  element->line_style = strdup("NONE");

  element->fill_style = strdup("NONE");

  element->color = color_create();
  color_none(element->color);
  color_set_tag(element->color, "color");

  design_element_set_type(element, design_element_type_point);

  return element;
}

void design_element_destroy_void(void *v)
{
  design_element_destroy((design_element_s *)v);
}

void design_element_destroy(design_element_s *e)
{
  assert(e);

  if (e->line_style) free(e->line_style);
  if (e->fill_style) free(e->fill_style);

  if (e->color) color_destroy(e->color);

  switch (e->type)
  {
    case design_element_type_dimension:
      if (e->dimension) design_dimension_destroy(e->dimension);
      break;
    case design_element_type_elliptic:
      if (e->elliptic) design_elliptic_destroy(e->elliptic);
      break;
    case design_element_type_line:
      if (e->line) design_line_destroy(e->line);
      break;
    case design_element_type_point:
      if (e->point) design_point_destroy(e->point);
      break;
    case design_element_type_polyline:
      if (e->polyline) design_polyline_destroy(e->polyline);
      break;
    case design_element_type_spline:
      if (e->spline) design_spline_destroy(e->spline);
      break;
    case design_element_type_text:
      if (e->text) design_text_destroy(e->text);
      break;
    case design_element_type_tolerance:
      if (e->tolerance) design_tolerance_destroy(e->tolerance);
      break;
    default: break;
  }
  free(e);
}

design_element_s *design_element_copy(design_element_s *e)
{
  design_element_s *ne;

  assert(e);

  ne = design_element_create();
  memcpy(ne, e, sizeof(design_element_s));

  if (e->color) ne->color = color_copy(e->color);

  switch (e->type)
  {
    case design_element_type_dimension:
      if (e->dimension) ne->dimension = design_dimension_copy(e->dimension);
      break;
    case design_element_type_elliptic:
      if (e->elliptic) ne->elliptic = design_elliptic_copy(e->elliptic);
      break;
    case design_element_type_line:
      if (e->line) ne->line = design_line_copy(e->line);
      break;
    case design_element_type_point:
      if (e->point) ne->point = design_point_copy(e->point);
      break;
    case design_element_type_polyline:
      if (e->polyline) ne->polyline = design_polyline_copy(e->polyline);
      break;
    case design_element_type_spline:
      if (e->spline) ne->spline = design_spline_copy(e->spline);
      break;
    case design_element_type_text:
      if (e->text) ne->text = design_text_copy(e->text);
      break;
    case design_element_type_tolerance:
      if (e->tolerance) ne->tolerance = design_tolerance_copy(e->tolerance);
      break;
    default: break;
  }

  return ne;
}

void design_element_set(design_element_s *e,
                        int id,
                        design_element_t type,
                        units_t units,
                        double line_weight,
                        char *line_style,
                        char *fill_style,
                        color_s *color,
                        void *data)
{
  assert(e);
  assert(line_style);
  assert(fill_style);
  assert(color);
  assert(data);

  design_element_set_id(e, id);
  design_element_set_type(e, type);
  design_element_set_units(e, units);
  design_element_set_line_weight(e, line_weight);
  design_element_set_line_style(e, line_style);
  design_element_set_fill_style(e, fill_style);
  design_element_set_color(e, color);
  switch (e->type)
  {
    case design_element_type_dimension:
      design_element_set_dimension(e, (design_dimension_s *)data);
      break;
    case design_element_type_elliptic:
      design_element_set_elliptic(e, (design_elliptic_s *)data);
      break;
    case design_element_type_line:
      design_element_set_line(e, (design_line_s *)data);
      break;
    case design_element_type_point:
      design_element_set_point(e, (design_point_s *)data);
      break;
    case design_element_type_polyline:
      design_element_set_polyline(e, (design_polyline_s *)data);
      break;
    case design_element_type_spline:
      design_element_set_spline(e, (design_spline_s *)data);
      break;
    case design_element_type_text:
      design_element_set_text(e, (design_text_s *)data);
      break;
    case design_element_type_tolerance:
      design_element_set_tolerance(e, (design_tolerance_s *)data);
      break;
    default: break;
  }
}

void design_element_get(design_element_s *e,
                        int *id,
                        design_element_t *type,
                        units_t *units,
                        double *line_weight,
                        char **line_style,
                        char **fill_style,
                        color_s **color,
                        void **data)
{
  assert(e);
  assert(id);
  assert(type);
  assert(units);
  assert(line_weight);
  assert(line_style);
  assert(fill_style);
  assert(color);
  assert(data);

  *id = design_element_get_id(e);
  *type = design_element_get_type(e);
  *units = design_element_get_units(e);
  *line_weight = design_element_get_line_weight(e);
  *line_style = design_element_get_line_style(e);
  *fill_style = design_element_get_fill_style(e);
  *color = design_element_get_color(e);
  switch (e->type)
  {
    case design_element_type_dimension:
      *data = design_element_get_dimension(e);
      break;
    case design_element_type_elliptic:
      *data = design_element_get_elliptic(e);
      break;
    case design_element_type_line:
      *data = design_element_get_line(e);
      break;
    case design_element_type_point:
      *data = design_element_get_point(e);
      break;
    case design_element_type_polyline:
      *data = design_element_get_polyline(e);
      break;
    case design_element_type_spline:
      *data = design_element_get_spline(e);
      break;
    case design_element_type_text:
      *data = design_element_get_text(e);
      break;
    case design_element_type_tolerance:
      *data = design_element_get_tolerance(e);
      break;
    default: break;
  }
}

void design_element_set_id(design_element_s *e, int id)
{
  assert(e);
  e->id = id;
}

int design_element_get_id(design_element_s *e)
{
  assert(e);
  return e->id;
}

void design_element_set_type(design_element_s *e, design_element_t type)
{
  assert(e);

  switch (e->type)
  {
    case design_element_type_dimension:
      if (e->dimension) design_dimension_destroy(e->dimension);
      break;
    case design_element_type_elliptic:
      if (e->elliptic) design_elliptic_destroy(e->elliptic);
      break;
    case design_element_type_line:
      if (e->line) design_line_destroy(e->line);
      break;
    case design_element_type_point:
      if (e->point) design_point_destroy(e->point);
      break;
    case design_element_type_polyline:
      if (e->polyline) design_polyline_destroy(e->polyline);
      break;
    case design_element_type_spline:
      if (e->spline) design_spline_destroy(e->spline);
      break;
    case design_element_type_text:
      if (e->text) design_text_destroy(e->text);
      break;
    case design_element_type_tolerance:
      if (e->tolerance) design_tolerance_destroy(e->tolerance);
      break;
    default: break;
  }

  e->type = type;

  switch (e->type)
  {
    case design_element_type_dimension:
      e->dimension = design_dimension_create();
      break;
    case design_element_type_elliptic:
      e->elliptic = design_elliptic_create();
      break;
    case design_element_type_line:
      e->line = design_line_create();
      break;
    case design_element_type_point:
      e->point = design_point_create();
      break;
    case design_element_type_polyline:
      e->polyline = design_polyline_create();
      break;
    case design_element_type_spline:
      e->spline = design_spline_create();
      break;
    case design_element_type_text:
      e->text = design_text_create();
      break;
    case design_element_type_tolerance:
      e->tolerance = design_tolerance_create();
      break;
    default: break;
  }
}

design_element_t design_element_get_type(design_element_s *e)
{
  assert(e);
  return e->type;
}

void design_element_set_units(design_element_s *e, units_t units)
{
  assert(e);
  e->units = units;
}

units_t design_element_get_units(design_element_s *e)
{
  return e->units;
}

void design_element_set_line_weight(design_element_s *e, double lw)
{
  assert(e);
  e->line_weight = lw;
}

double design_element_get_line_weight(design_element_s *e)
{
  assert(e);
  return e->line_weight;
}

void design_element_set_line_style(design_element_s *e, char *style)
{
  assert(e);
  if (e->line_style) free(e->line_style);
  e->line_style = strdup(style);
}

char *design_element_get_line_style(design_element_s *e)
{
  assert(e);
  return e->line_style;
}

void design_element_set_fill_style(design_element_s *e, char *style)
{
  assert(e);
  if (e->fill_style) free(e->fill_style);
  e->fill_style = strdup(style);
}

char *design_element_get_fill_style(design_element_s *e)
{
  assert(e);
  return e->fill_style;
}

void design_element_set_color(design_element_s *e, color_s *color)
{
  assert(e);
  assert(color);
  if (e->color) color_destroy(e->color);
  e->color = color;
  color_set_tag(e->color, "color");
}

color_s *design_element_get_color(design_element_s *e)
{
  assert(e);
  return e->color;
}

void design_element_set_dimension(design_element_s *e, design_dimension_s *d)
{
  assert(e);
  assert(d);

  design_element_set_type(e, design_element_type_dimension);
  design_dimension_destroy(e->dimension);
  e->dimension = d;
}

design_dimension_s *design_element_get_dimension(design_element_s *e)
{
  assert(e);
  return e->dimension;
}

void design_element_set_elliptic(design_element_s *e, design_elliptic_s *el)
{
  assert(e);
  assert(el);

  design_element_set_type(e, design_element_type_elliptic);
  design_elliptic_destroy(e->elliptic);
  e->elliptic = el;
}

design_elliptic_s *design_element_get_elliptic(design_element_s *e)
{
  assert(e);
  return e->elliptic;
}

void design_element_set_line(design_element_s *e, design_line_s *l)
{
  assert(e);
  assert(l);

  design_element_set_type(e, design_element_type_line);
  design_line_destroy(e->line);
  e->line = l;
}

design_line_s *design_element_get_line(design_element_s *e)
{
  assert(e);
  return e->line;
}

void design_element_set_point(design_element_s *e, design_point_s *p)
{
  assert(e);
  assert(p);

  design_element_set_type(e, design_element_type_point);
  design_point_destroy(e->point);
  e->point = p;
}

design_point_s *design_element_get_point(design_element_s *e)
{
  assert(e);
  return e->point;
}

void design_element_set_polyline(design_element_s *e, design_polyline_s *pl)
{
  assert(e);
  assert(pl);

  design_element_set_type(e, design_element_type_polyline);
  design_polyline_destroy(e->polyline);
  e->polyline = pl;
}

design_polyline_s *design_element_get_polyline(design_element_s *e)
{
  assert(e);
  return e->polyline;
}

void design_element_set_spline(design_element_s *e, design_spline_s *s)
{
  assert(e);
  assert(s);

  design_element_set_type(e, design_element_type_spline);
  design_spline_destroy(e->spline);
  e->spline = s;
}

design_spline_s *design_element_get_spline(design_element_s *e)
{
  assert(e);
  return e->spline;
}

void design_element_set_text(design_element_s *e, design_text_s *t)
{
  assert(e);
  assert(t);

  design_element_set_type(e, design_element_type_text);
  design_text_destroy(e->text);
  e->text = t;
}

design_text_s *design_element_get_text(design_element_s *e)
{
  assert(e);
  return e->text;
}

void design_element_set_tolerance(design_element_s *e, design_tolerance_s *t)
{
  assert(e);
  assert(t);

  design_element_set_type(e, design_element_type_tolerance);
  design_tolerance_destroy(e->tolerance);
  e->tolerance = t;
}

design_tolerance_s *design_element_get_tolerance(design_element_s *e)
{
  assert(e);
  return e->tolerance;
}

