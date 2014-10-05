#ifndef BLUE_DESIGN_LINE_STYLE_SEGMENT_PARMS_H
#define BLUE_DESIGN_LINE_STYLE_SEGMENT_PARMS_H

#include "design-line-style-segment.h"

typedef enum
{
  blue_design_line_style_segment_parameter_BEG = 2000,
  blue_design_line_style_segment_parameter_length =
    blue_design_line_style_segment_parameter_BEG,
  blue_design_line_style_segment_parameter_END
} blue_design_line_style_segment_parameter_t;

design_line_style_segment_s *blue_design_line_style_segment_parameter_handler(
  int argc, char** argv, design_line_style_segment_s *lss);
int blue_design_line_style_segment_check(design_line_style_segment_s *lss);
void blue_design_line_style_segment_check_error(void);
unsigned char blue_design_line_style_segment_get_change(
  blue_design_line_style_segment_parameter_t p);
void blue_design_line_style_segment_set_change(
  blue_design_line_style_segment_parameter_t p);
void blue_design_line_style_segment_unset_changes(void);

#endif // BLUE_DESIGN_LINE_STYLE_SEGMENT_PARMS_H
