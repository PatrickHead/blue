#ifndef DESIGN_LINE_STYLE_SEGMENTS_H
#define DESIGN_LINE_STYLE_SEGMENTS_H

#include "list.h"
#include "design-line-style-segment.h"

typedef struct
{
  list_s *line_style_segments;
} design_line_style_segments_s;

design_line_style_segments_s *design_line_style_segments_create(void);
void design_line_style_segments_destroy(design_line_style_segments_s *lsss);
design_line_style_segments_s *design_line_style_segments_copy(
  design_line_style_segments_s *lsss);
void design_line_style_segments_add_line_style_segment(
  design_line_style_segments_s *lsss,
  design_line_style_segment_s *lss);

#endif // DESIGN_LINE_STYLE_SEGMENTS_H
