#ifndef DESIGN_LINE_STYLES_H
#define DESIGN_LINE_STYLES_H

#include "list.h"
#include "design-line-style.h"

typedef struct
{
  list_s *line_styles;
} design_line_styles_s;

design_line_styles_s *design_line_styles_create(void);
void design_line_styles_destroy(design_line_styles_s *lss);
design_line_styles_s *design_line_styles_copy(design_line_styles_s *lss);
void design_line_styles_add_line_style(design_line_styles_s *lss,
                                       design_line_style_s *ls);
void design_line_styles_delete_line_style(design_line_styles_s *lss, char *name);
design_line_style_s *design_line_styles_get_line_style(design_line_styles_s *lss,
                                                       char *name);

#endif // DESIGN_LINE_STYLES_H
