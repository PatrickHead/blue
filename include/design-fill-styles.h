#ifndef DESIGN_FILL_STYLES_H
#define DESIGN_FILL_STYLES_H

#include "list.h"
#include "design-fill-style.h"

typedef struct
{
  list_s *fill_styles;
} design_fill_styles_s;

design_fill_styles_s *design_fill_styles_create(void);
void design_fill_styles_destroy(design_fill_styles_s *fss);
design_fill_styles_s *design_fill_styles_copy(design_fill_styles_s *fss);
void design_fill_styles_add_fill_style(design_fill_styles_s *fss,
                                       design_fill_style_s *fs);
void design_fill_styles_delete_fill_style(design_fill_styles_s *fss, char *name);
design_fill_style_s *design_fill_styles_get_fill_style(design_fill_styles_s *fss,
                                                       char *name);

#endif // DESIGN_FILL_STYLES_H
