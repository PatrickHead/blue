#ifndef BLUE_DESIGN_LINE_STYLE_PARMS_H
#define BLUE_DESIGN_LINE_STYLE_PARMS_H

#include "design-line-style.h"

typedef enum
{
  blue_design_line_style_parameter_BEG = 2000,
  blue_design_line_style_parameter_name,
  blue_design_line_style_parameter_segments_xml,
  blue_design_line_style_parameter_END
} blue_design_line_style_parameter_t;

design_line_style_s *blue_design_line_style_parameter_handler(int argc,
                                                              char** argv,
                                                         design_line_style_s *ls);
int blue_design_line_style_check(design_line_style_s *ls);
void blue_design_line_style_check_error(void);
unsigned char blue_design_line_style_get_change(
  blue_design_line_style_parameter_t p);
void blue_design_line_style_set_change(
  blue_design_line_style_parameter_t p);
void blue_design_line_style_unset_changes(void);

#endif // BLUE_DESIGN_LINE_STYLE_PARMS_H
