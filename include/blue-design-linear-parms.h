#ifndef BLUE_DESIGN_LINEAR_PARMS_H
#define BLUE_DESIGN_LINEAR_PARMS_H

#include "design-linear.h"

typedef enum
{
  blue_design_linear_parameter_BEG = 2000,
  blue_design_linear_parameter_start = blue_design_linear_parameter_BEG,
  blue_design_linear_parameter_end,
  blue_design_linear_parameter_gap,
  blue_design_linear_parameter_extension_above,
  blue_design_linear_parameter_extension_below,
  blue_design_linear_parameter_dimension,
  blue_design_linear_parameter_defaults_xml,
  blue_design_linear_parameter_END
} blue_design_linear_parameter_t;

design_linear_s *blue_design_linear_parameter_handler(int argc,
                                                      char** argv,
                                                      design_linear_s *l);
int blue_design_linear_check(design_linear_s *l);
void blue_design_linear_check_error(void);
unsigned char blue_design_linear_get_change(blue_design_linear_parameter_t p);
void blue_design_linear_set_change(blue_design_linear_parameter_t p);
void blue_design_linear_unset_changes(void);

#endif // BLUE_DESIGN_LINEAR_PARMS_H
