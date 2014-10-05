#ifndef DESIGN_DEFAULTS_H
#define DESIGN_DEFAULTS_H

#include "units.h"

#include "color.h"

typedef struct
{
  units_t units;
  double line_weight;
  char *line_style;
  char *fill_style;
  double dimension_text_size;
  int dimension_precision;
  double angular_gap;
  double angular_extension;
  double linear_gap;
  double linear_extension_above;
  double linear_extension_below;
  double tolerance_text_size;
  double tolerance_plus;
  double tolerance_minus;
  int tolerance_precision;
  color_s *background_color;
  color_s *element_color;
} design_defaults_s;

design_defaults_s *design_defaults_create(void);
void design_defaults_destroy_void(void *v);
void design_defaults_destroy(design_defaults_s *d);
design_defaults_s *design_defaults_copy(design_defaults_s *d);
void design_defaults_push(design_defaults_s *d);
design_defaults_s *design_defaults_pop(void);
design_defaults_s *design_defaults_current(void);

void design_defaults_set(design_defaults_s *d,
                         units_t units,
                         double line_weight,
                         char *line_style,
                         char *fill_style,
                         double dimension_text_size,
                         int dimension_precision,
                         double angular_gap,
                         double angular_extension,
                         double linear_gap,
                         double linear_extension_above,
                         double linear_extension_below,
                         double tolerance_text_size,
                         double tolerance_plus,
                         double tolerance_minus,
                         int tolerance_precision,
                         color_s *background_color,
                         color_s *element_color);
void design_defaults_get(design_defaults_s *d,
                         units_t *units,
                         double *line_weight,
                         char **line_style,
                         char **fill_style,
                         double *dimension_text_size,
                         int *dimension_precision,
                         double *angular_gap,
                         double *angular_extension,
                         double *linear_gap,
                         double *linear_extension_above,
                         double *linear_extension_below,
                         double *tolerance_text_size,
                         double *tolerance_plus,
                         double *tolerance_minus,
                         int *tolerance_precision,
                         color_s **background_color,
                         color_s **element_color);

void design_defaults_set_units(design_defaults_s *d, units_t units);
units_t design_defaults_get_units(design_defaults_s *d);

void design_defaults_set_line_weight(design_defaults_s *d, double line_weight);
double design_defaults_get_line_weight(design_defaults_s *d);

void design_defaults_set_line_style(design_defaults_s *d, char *line_style);
char *design_defaults_get_line_style(design_defaults_s *d);

void design_defaults_set_fill_style(design_defaults_s *d, char *fill_style);
char *design_defaults_get_fill_style(design_defaults_s *d);

void design_defaults_set_dimension_text_size(design_defaults_s *d, double size);
double design_defaults_get_dimension_text_size(design_defaults_s *d);

void design_defaults_set_dimension_precision(design_defaults_s *d, int precision);
int design_defaults_get_dimension_precision(design_defaults_s *d);

void design_defaults_set_angular_gap(design_defaults_s *d, double gap);
double design_defaults_get_angular_gap(design_defaults_s *d);

void design_defaults_set_angular_extension(design_defaults_s *d,
                                           double extension);
double design_defaults_get_angular_extension(design_defaults_s *d);

void design_defaults_set_linear_gap(design_defaults_s *d, double gap);
double design_defaults_get_linear_gap(design_defaults_s *d);

void design_defaults_set_linear_extension_above(design_defaults_s *d,
                                                double extension);
double design_defaults_get_linear_extension_above(design_defaults_s *d);

void design_defaults_set_linear_extension_below(design_defaults_s *d,
                                                double extension);
double design_defaults_get_linear_extension_below(design_defaults_s *d);

void design_defaults_set_tolerance_text_size(design_defaults_s *d, double size);
double design_defaults_get_tolerance_text_size(design_defaults_s *d);

void design_defaults_set_tolerance_plus(design_defaults_s *d, double plus);
double design_defaults_get_tolerance_plus(design_defaults_s *d);

void design_defaults_set_tolerance_minus(design_defaults_s *d, double minus);
double design_defaults_get_tolerance_minus(design_defaults_s *d);

void design_defaults_set_tolerance_precision(design_defaults_s *d, int precision);
int design_defaults_get_tolerance_precision(design_defaults_s *d);

void design_defaults_set_background_color(design_defaults_s *d, color_s *color);
color_s *design_defaults_get_background_color(design_defaults_s *d);

void design_defaults_set_element_color(design_defaults_s *d, color_s *color);
color_s *design_defaults_get_element_color(design_defaults_s *d);

#endif // DESIGN_DEFAULTS_H
