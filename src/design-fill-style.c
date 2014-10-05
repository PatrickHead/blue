#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-line-style.h"
#include "design-fill-style.h"

design_fill_style_s *design_fill_style_create(void)
{
  design_fill_style_s *fill_style;

  fill_style = (design_fill_style_s *)malloc(sizeof(design_fill_style_s));
  memset(fill_style, 0, sizeof(design_fill_style_s));

  fill_style->name = strdup("NONE");
  fill_style->line_weight = 1.0;
  fill_style->line_style = strdup("NONE");
  fill_style->background_color = color_create();
  color_none(fill_style->background_color);
  color_set_tag(fill_style->background_color, "background-color");
  fill_style->pattern_color = color_create();
  color_black(fill_style->pattern_color);
  color_set_tag(fill_style->pattern_color, "pattern-color");

  return fill_style;
}

void design_fill_style_destroy_void(void *v)
{
  assert(v);
  design_fill_style_destroy((design_fill_style_s *)v);
}

void design_fill_style_destroy(design_fill_style_s *fs)
{
  assert(fs);
  if (fs->name) free(fs->name);
  if (fs->line_style) free(fs->line_style);
  if (fs->background_color) color_destroy(fs->background_color);
  if (fs->pattern_color) color_destroy(fs->pattern_color);
  if (fs->source) free(fs->source);
  free(fs);
}

design_fill_style_s *design_fill_style_copy(design_fill_style_s *fs)
{
  design_fill_style_s *nfs;

  assert(fs);

  nfs = design_fill_style_create();
  memcpy(nfs, fs, sizeof(design_fill_style_s));

  if (fs->name) nfs->name = strdup(fs->name);
  if (fs->line_style)
    nfs->line_style = strdup(fs->line_style);
  if (fs->background_color)
    nfs->background_color = color_copy(fs->background_color);
  if (fs->pattern_color)
    nfs->pattern_color = color_copy(fs->pattern_color);
  if (fs->source) nfs->source = strdup(fs->source);

  return nfs;
}

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
                           char *source)
{
  assert(fs);
  assert(name);
  assert(source);

  design_fill_style_set_name(fs, name);
  design_fill_style_set_type(fs, type);
  design_fill_style_set_line_weight(fs, line_weight);
  design_fill_style_set_line_style(fs, line_style);
  design_fill_style_set_background_color(fs, background_color);
  design_fill_style_set_pattern_color(fs, pattern_color);
  design_fill_style_set_angle1(fs, angle1);
  design_fill_style_set_spacing1(fs, spacing1);
  design_fill_style_set_angle2(fs, angle2);
  design_fill_style_set_spacing2(fs, spacing2);
  design_fill_style_set_source(fs, source);
}

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
                           char **source)
{
  assert(fs);
  assert(name);
  assert(type);
  assert(line_weight);
  assert(line_style);
  assert(background_color);
  assert(pattern_color);
  assert(angle1);
  assert(spacing1);
  assert(angle2);
  assert(spacing2);
  assert(source);

  *name = design_fill_style_get_name(fs);
  *type = design_fill_style_get_type(fs);
  *line_weight = design_fill_style_get_line_weight(fs);
  *line_style = design_fill_style_get_line_style(fs);
  *background_color = design_fill_style_get_background_color(fs);
  *pattern_color = design_fill_style_get_pattern_color(fs);
  *angle1 = design_fill_style_get_angle1(fs);
  *spacing1 = design_fill_style_get_spacing1(fs);
  *angle2 = design_fill_style_get_angle2(fs);
  *spacing2 = design_fill_style_get_spacing2(fs);
  *source = design_fill_style_get_source(fs);
}

void design_fill_style_set_name(design_fill_style_s *fs, char *name)
{
  assert(fs);
  assert(name);

  if (fs->name) free(fs->name);
  fs->name = strdup(name);
}

char *design_fill_style_get_name(design_fill_style_s *fs)
{
  assert(fs);
  return fs->name;
}

void design_fill_style_set_line_weight(design_fill_style_s *fs,
                                       double line_weight)
{
  assert(fs);

  fs->line_weight = line_weight;
}

double design_fill_style_get_line_weight(design_fill_style_s *fs)
{
  assert(fs);
  return fs->line_weight;
}

void design_fill_style_set_line_style(design_fill_style_s *fs,
                                      char *line_style)
{
  assert(fs);
  assert(line_style);

  if (fs->line_style) free(fs->line_style);
  fs->line_style = strdup(line_style);
}

char *design_fill_style_get_line_style(design_fill_style_s *fs)
{
  assert(fs);
  return fs->line_style;
}

void design_fill_style_set_background_color(design_fill_style_s *fs,
                                            color_s *background_color)
{
  assert(fs);
  assert(background_color);

  if (fs->background_color) color_destroy(fs->background_color);
  fs->background_color = color_copy(background_color);
}

color_s *design_fill_style_get_background_color(design_fill_style_s *fs)
{
  assert(fs);
  return fs->background_color;
}

void design_fill_style_set_pattern_color(design_fill_style_s *fs,
                                         color_s *pattern_color)
{
  assert(fs);
  assert(pattern_color);

  if (fs->pattern_color) color_destroy(fs->pattern_color);
  fs->pattern_color = color_copy(pattern_color);
}

color_s *design_fill_style_get_pattern_color(design_fill_style_s *fs)
{
  assert(fs);
  return fs->pattern_color;
}

void design_fill_style_set_type(design_fill_style_s *fs,
                                design_fill_style_t type)
{
  assert(fs);
  fs->type = type;
}

design_fill_style_t design_fill_style_get_type(design_fill_style_s *fs)
{
  assert(fs);
  return fs->type;
}

void design_fill_style_set_angle1(design_fill_style_s *fs, double angle)
{
  assert(fs);
  fs->angle1 = angle;
}

double design_fill_style_get_angle1(design_fill_style_s *fs)
{
  assert(fs);
  return fs->angle1;
}

void design_fill_style_set_spacing1(design_fill_style_s *fs, double spacing)
{
  assert(fs);
  fs->spacing1 = spacing;
}

double design_fill_style_get_spacing1(design_fill_style_s *fs)
{
  assert(fs);
  return fs->spacing1;
}

void design_fill_style_set_angle2(design_fill_style_s *fs, double angle)
{
  assert(fs);
  fs->angle2 = angle;
}

double design_fill_style_get_angle2(design_fill_style_s *fs)
{
  assert(fs);
  return fs->angle2;
}

void design_fill_style_set_spacing2(design_fill_style_s *fs, double spacing)
{
  assert(fs);
  fs->spacing2 = spacing;
}

double design_fill_style_get_spacing2(design_fill_style_s *fs)
{
  assert(fs);
  return fs->spacing2;
}

void design_fill_style_set_source(design_fill_style_s *fs, char *source)
{
  assert(fs);
  assert(source);

  if (fs->source) free(fs->source);
  fs->source = strdup(source);
}

char *design_fill_style_get_source(design_fill_style_s *fs)
{
  assert(fs);
  return fs->source;
}

