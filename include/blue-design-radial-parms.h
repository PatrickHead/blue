#ifndef BLUE_DESIGN_RADIAL_PARMS_H
#define BLUE_DESIGN_RADIAL_PARMS_H

#include "design-radial.h"

typedef enum
{
  blue_design_radial_parameter_BEG = 2000,
  blue_design_radial_parameter__type = blue_design_radial_parameter_BEG,
  blue_design_radial_parameter_center,
  blue_design_radial_parameter_major,
  blue_design_radial_parameter_minor,
  blue_design_radial_parameter_angle,
  blue_design_radial_parameter_leader,
  blue_design_radial_parameter_defaults_xml,
  blue_design_radial_parameter_END
} blue_design_radial_parameter_t;

design_radial_s *blue_design_radial_parameter_handler(int argc,
                                                      char** argv,
                                                      design_radial_s *r);
int blue_design_radial_check(design_radial_s *r);
void blue_design_radial_check_error(void);
unsigned char blue_design_radial_get_change(
                blue_design_radial_parameter_t p);
void blue_design_radial_set_change(blue_design_radial_parameter_t p);
void blue_design_radial_unset_changes(void);

#endif // BLUE_DESIGN_RADIAL_PARMS_H
