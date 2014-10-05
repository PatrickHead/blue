#ifndef BLUE_DESIGN_DEFAULTS_PARMS_H
#define BLUE_DESIGN_DEFAULTS_PARMS_H

#include "design-defaults.h"

typedef enum
{
  blue_design_defaults_parameter_BEG = 2000,
  blue_design_defaults_parameter_units,
  blue_design_defaults_parameter_line_weight,
  blue_design_defaults_parameter_line_style,
  blue_design_defaults_parameter_fill_style,
  blue_design_defaults_parameter_dimension_text_size,
  blue_design_defaults_parameter_dimension_precision,
  blue_design_defaults_parameter_angular_gap,
  blue_design_defaults_parameter_angular_extension,
  blue_design_defaults_parameter_linear_gap,
  blue_design_defaults_parameter_linear_extension_above,
  blue_design_defaults_parameter_linear_extension_below,
  blue_design_defaults_parameter_tolerance_text_size,
  blue_design_defaults_parameter_tolerance_plus,
  blue_design_defaults_parameter_tolerance_minus,
  blue_design_defaults_parameter_tolerance_precision,
  blue_design_defaults_parameter_background_color_xml,
  blue_design_defaults_parameter_element_color_xml,
  blue_design_defaults_parameter_END
} blue_design_defaults_parameter_t;

design_defaults_s *blue_design_defaults_parameter_handler(int argc,
                                                          char** argv,
                                                          design_defaults_s *d);
int blue_design_defaults_check(design_defaults_s *d);
void blue_design_defaults_check_error(void);
unsigned char blue_design_defaults_get_change(
  blue_design_defaults_parameter_t p);
void blue_design_defaults_set_change(blue_design_defaults_parameter_t p);
void blue_design_defaults_unset_changes(void);

#endif // BLUE_DESIGN_DEFAULTS_PARMS_H
