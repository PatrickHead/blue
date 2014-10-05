#ifndef BLUE_DESIGN_FILL_STYLE_PARMS_H
#define BLUE_DESIGN_FILL_STYLE_PARMS_H

#include "design-fill-style.h"

typedef enum
{
  blue_design_fill_style_parameter_BEG = 2000,
  blue_design_fill_style_parameter_name,
  blue_design_fill_style_parameter_TYPE,
  blue_design_fill_style_parameter_line_weight,
  blue_design_fill_style_parameter_line_style,
  blue_design_fill_style_parameter_background_color_xml,
  blue_design_fill_style_parameter_pattern_color_xml,
  blue_design_fill_style_parameter_angle1,
  blue_design_fill_style_parameter_spacing1,
  blue_design_fill_style_parameter_angle2,
  blue_design_fill_style_parameter_spacing2,
  blue_design_fill_style_parameter_source,
  blue_design_fill_style_parameter_END
} blue_design_fill_style_parameter_t;

design_fill_style_s *blue_design_fill_style_parameter_handler(int argc,
                                                              char** argv,
                                                         design_fill_style_s *fs);
int blue_design_fill_style_check(design_fill_style_s *fs);
void blue_design_fill_style_check_error(void);
unsigned char blue_design_fill_style_get_change(
  blue_design_fill_style_parameter_t p);
void blue_design_fill_style_set_change(blue_design_fill_style_parameter_t p);
void blue_design_fill_style_unset_changes(void);

#endif // BLUE_DESIGN_FILL_STYLE_PARMS_H
