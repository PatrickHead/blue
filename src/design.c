#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "design-defaults.h"

#include "design.h"

design_s *design_create(void)
{
  design_s *d;

  d = (design_s *)malloc(sizeof(design_s));
  memset(d, 0, sizeof(design_s));

  d->defaults = design_defaults_create();
  d->line_styles = design_line_styles_create();
  d->fill_styles = design_fill_styles_create();
  d->layers = design_layers_create();

  return d;
}

void design_destroy(design_s *d)
{
  assert(d);

  if (d->defaults) design_defaults_destroy(d->defaults);
  if (d->line_styles) design_line_styles_destroy(d->line_styles);
  if (d->fill_styles) design_fill_styles_destroy(d->fill_styles);
  if (d->layers) design_layers_destroy(d->layers);

  free(d);
}

design_s *design_copy(design_s *d)
{
  design_s *nd;

  assert(d);

  nd = design_create();
  memcpy(nd, d, sizeof(design_s));

  if (d->defaults) nd->defaults = design_defaults_copy(d->defaults);
  if (d->line_styles) nd->line_styles = design_line_styles_copy(d->line_styles);
  if (d->fill_styles) nd->fill_styles = design_fill_styles_copy(d->fill_styles);
  if (d->layers) nd->layers = design_layers_copy(d->layers);

  return nd;
}

void design_set(design_s *d,
                design_defaults_s *defaults,
                design_line_styles_s *line_styles,
                design_fill_styles_s *fill_styles,
                design_layers_s *layers)
{
  assert(d);
  assert(defaults);
  assert(line_styles);
  assert(fill_styles);
  assert(layers);

  design_set_defaults(d, defaults);
  design_set_line_styles(d, line_styles);
  design_set_fill_styles(d, fill_styles);
  design_set_layers(d, layers);
}

void design_get(design_s *d,
                design_defaults_s **defaults,
                design_line_styles_s **line_styles,
                design_fill_styles_s **fill_styles,
                design_layers_s **layers)
{
  assert(d);
  assert(defaults);
  assert(line_styles);
  assert(fill_styles);
  assert(layers);

  *defaults = design_get_defaults(d);
  *line_styles = design_get_line_styles(d);
  *fill_styles = design_get_fill_styles(d);
  *layers = design_get_layers(d);
}

void design_set_defaults(design_s *d, design_defaults_s *dflts)
{
  assert(d);
  assert(dflts);

  if (d->defaults) design_defaults_destroy(d->defaults);
  d->defaults = design_defaults_copy(dflts);
}

design_defaults_s *design_get_defaults(design_s *d)
{
  assert(d);
  return d->defaults;
}

void design_set_line_styles(design_s *d, design_line_styles_s *lss)
{
  assert(d);
  assert(lss);

  if (d->line_styles) design_line_styles_destroy(d->line_styles);
  d->line_styles = design_line_styles_copy(lss);
}

design_line_styles_s *design_get_line_styles(design_s *d)
{
  assert(d);
  return d->line_styles;
}

void design_set_fill_styles(design_s *d, design_fill_styles_s *lss)
{
  assert(d);
  assert(lss);

  if (d->fill_styles) design_fill_styles_destroy(d->fill_styles);
  d->fill_styles = design_fill_styles_copy(lss);
}

design_fill_styles_s *design_get_fill_styles(design_s *d)
{
  assert(d);
  return d->fill_styles;
}

void design_set_layers(design_s *d, design_layers_s *ls)
{
  assert(d);
  assert(ls);

  if (d->layers) design_layers_destroy(d->layers);
  d->layers = design_layers_copy(ls);
}

design_layers_s *design_get_layers(design_s *d)
{
  assert(d);
  return d->layers;
}

