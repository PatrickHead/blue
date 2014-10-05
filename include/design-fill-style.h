#ifndef DESIGN_FILL_STYLE_H
#define DESIGN_FILL_STYLE_H

#include "color.h"

#include "design-fill-style-type.h"

typedef struct
{
  char *name;
  design_fill_style_t type;
  double line_weight;
  char *line_style;
  color_s *background_color;
  color_s *pattern_color;
  double angle1;
  double spacing1;
  double angle2;
  double spacing2;
  char *source;
} design_fill_style_s;

design_fill_style_s *design_fill_style_create(void);
void design_fill_style_destroy_void(void *v);
void design_fill_style_destroy(design_fill_style_s *fs);
design_fill_style_s *design_fill_style_copy(design_fill_style_s *fs);

void design_fill_style_set(design_fill_style_s *fs,
                           char *name,
                           design_fill_style_t type,
                           double line_weight,
                           char *line_style,
                           color_s *background_color,
                           color_s *pattern_color,
                           double angle1,
                           double spacing1,
                           double angle2,
                           double spacing2,
                           char *source);
void design_fill_style_get(design_fill_style_s *fs,
                           char **name,
                           design_fill_style_t *type,
                           double *line_weight,
                           char **line_style,
                           color_s **background_color,
                           color_s **pattern_color,
                           double *angle1,
                           double *spacing1,
                           double *angle2,
                           double *spacing2,
                           char **source);

void design_fill_style_set_name(design_fill_style_s *fs, char *name);
char *design_fill_style_get_name(design_fill_style_s *fs);

void design_fill_style_set_type(design_fill_style_s *fs,
                                design_fill_style_t type);
design_fill_style_t design_fill_style_get_type(design_fill_style_s *fs);

void design_fill_style_set_line_weight(design_fill_style_s *fs,
                                       double line_weight);
double design_fill_style_get_line_weight(design_fill_style_s *fs);

void design_fill_style_set_line_style(design_fill_style_s *fs,
                                      char *line_style);
char *design_fill_style_get_line_style(design_fill_style_s *fs);

void design_fill_style_set_background_color(design_fill_style_s *fs,
                                            color_s *background_color);
color_s *design_fill_style_get_background_color(design_fill_style_s *fs);

void design_fill_style_set_pattern_color(design_fill_style_s *fs,
                                         color_s *pattern_color);
color_s *design_fill_style_get_pattern_color(design_fill_style_s *fs);

void design_fill_style_set_angle1(design_fill_style_s *fs, double angle);
double design_fill_style_get_angle1(design_fill_style_s *fs);

void design_fill_style_set_spacing1(design_fill_style_s *fs, double spacing);
double design_fill_style_get_spacing1(design_fill_style_s *fs);

void design_fill_style_set_angle2(design_fill_style_s *fs, double angle);
double design_fill_style_get_angle2(design_fill_style_s *fs);

void design_fill_style_set_spacing2(design_fill_style_s *fs, double spacing);
double design_fill_style_get_spacing2(design_fill_style_s *fs);

void design_fill_style_set_source(design_fill_style_s *fs, char *source);
char *design_fill_style_get_source(design_fill_style_s *fs);

#endif // DESIGN_FILL_STYLE_H
