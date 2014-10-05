#ifndef DESIGN_H
#define DESIGN_H

#include "design-defaults.h"
#include "design-line-styles.h"
#include "design-fill-styles.h"
#include "design-layers.h"

typedef struct
{
  design_defaults_s *defaults;
  design_line_styles_s *line_styles;
  design_fill_styles_s *fill_styles;
  design_layers_s *layers;
} design_s;

design_s *design_create(void);
void design_destroy(design_s *d);
design_s *design_copy(design_s *d);

void design_set(design_s *d,
                design_defaults_s *defaults,
                design_line_styles_s *line_styles,
                design_fill_styles_s *fill_styles,
                design_layers_s *layers);
void design_get(design_s *d,
                design_defaults_s **defaults,
                design_line_styles_s **line_styles,
                design_fill_styles_s **fill_styles,
                design_layers_s **layers);

void design_set_defaults(design_s *d, design_defaults_s *dflts);
design_defaults_s *design_get_defaults(design_s *d);

void design_set_line_styles(design_s *d, design_line_styles_s *lss);
design_line_styles_s *design_get_line_styles(design_s *d);

void design_set_fill_styles(design_s *d, design_fill_styles_s *lss);
design_fill_styles_s *design_get_fill_styles(design_s *d);

void design_set_layers(design_s *d, design_layers_s *ls);
design_layers_s *design_get_layers(design_s *d);

#endif // DESIGN_H

