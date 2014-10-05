#ifndef BLUE_DESIGN_LINE_STYLE_SEGMENTS_PARMS_H
#define BLUE_DESIGN_LINE_STYLE_SEGMENTS_PARMS_H

#include "design-line-style-segments.h"

typedef enum
{
  blue_design_line_style_segments_parameter_BEG = 2000,
  blue_design_line_style_segments_parameter_segment_xml,
  blue_design_line_style_segments_parameter_END
} blue_design_line_style_segments_parameter_t;

design_line_style_segments_s *blue_design_line_style_segments_parameter_handler(
  int argc, char** argv, design_line_style_segments_s *lsss);
int blue_design_line_style_segments_check(design_line_style_segments_s *lsss);
void blue_design_line_style_segments_check_error(void);
unsigned char blue_design_line_style_segments_get_change(
  blue_design_line_style_segments_parameter_t p);
void blue_design_line_style_segments_set_change(
  blue_design_line_style_segments_parameter_t p);
void blue_design_line_style_segments_unset_changes(void);

#endif // BLUE_DESIGN_LINE_STYLE_SEGMENTS_PARMS_H
