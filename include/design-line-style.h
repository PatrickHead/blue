#ifndef DESIGN_LINE_STYLE_H
#define DESIGN_LINE_STYLE_H

#include "list.h"

#include "design-line-style-segments.h"

typedef struct
{
  char *name;
  design_line_style_segments_s *line_style_segments;
} design_line_style_s;

design_line_style_s *design_line_style_create(void);
void design_line_style_destroy_void(void *v);
void design_line_style_destroy(design_line_style_s *dls);
design_line_style_s *design_line_style_copy(design_line_style_s *dls);

void design_line_style_set(design_line_style_s *dls,
                           char *name,
                           design_line_style_segments_s *line_style_segments);
void design_line_style_get(design_line_style_s *dls,
                           char **name,
                           design_line_style_segments_s **line_style_segments);

void design_line_style_set_name(design_line_style_s *dls, char *name);
char *design_line_style_get_name(design_line_style_s *dls);

void design_line_style_set_line_style_segments(design_line_style_s *dls,
                                              design_line_style_segments_s *lsss);
design_line_style_segments_s *design_line_style_get_line_style_segments(
  design_line_style_s *dls);

void design_line_style_add_segment(design_line_style_s *dls,
                                   design_line_style_segment_s *lss);

#endif // DESIGN_LINE_STYLE_H
