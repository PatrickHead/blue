#ifndef BLUE_DESIGN_ANGULAR_PARMS_H
#define BLUE_DESIGN_ANGULAR_PARMS_H

#include "design-angular.h"

typedef enum
{
  blue_design_angular_parameter_BEG = 2000,
  blue_design_angular_parameter_angle = blue_design_angular_parameter_BEG,
  blue_design_angular_parameter_alpha,
  blue_design_angular_parameter_beta,
  blue_design_angular_parameter_gamma,
  blue_design_angular_parameter_gap,
  blue_design_angular_parameter_extension,
  blue_design_angular_parameter_defaults_xml,
  blue_design_angular_parameter_END
} blue_design_angular_parameter_t;

design_angular_s *blue_design_angular_parameter_handler(int argc,
                                                        char** argv,
                                                        design_angular_s *a);
int blue_design_angular_check(design_angular_s *a);
void blue_design_angular_check_error(void);
unsigned char blue_design_angular_get_change(
                blue_design_angular_parameter_t p);
void blue_design_angular_set_change(blue_design_angular_parameter_t p);
void blue_design_angular_unset_changes(void);

#endif // BLUE_DESIGN_ANGULAR_PARMS_H
