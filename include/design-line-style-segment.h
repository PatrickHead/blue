#ifndef DESIGN_LINE_STYLE_SEGMENT_H
#define DESIGN_LINE_STYLE_SEGMENT_H

typedef struct
{
  double length;
} design_line_style_segment_s;

design_line_style_segment_s *design_line_style_segment_create(void);
void design_line_style_segment_destroy_void(void *v);
void design_line_style_segment_destroy(design_line_style_segment_s *lss);
design_line_style_segment_s *design_line_style_segment_copy(
  design_line_style_segment_s *lss);

void design_line_style_segment_set(design_line_style_segment_s *lss,
                      double length);
void design_line_style_segment_get(design_line_style_segment_s *lss,
                      double *length);

void design_line_style_segment_set_length(design_line_style_segment_s *lss,
                                          double length); 
double design_line_style_segment_get_length(design_line_style_segment_s *lss);

#endif // DESIGN_LINE_STYLE_SEGMENT_H
