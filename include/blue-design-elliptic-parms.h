#ifndef BLUE_DESIGN_ELLIPTIC_PARMS_H
#define BLUE_DESIGN_ELLIPTIC_PARMS_H

#include "design-elliptic.h"

typedef enum
{
  blue_design_elliptic_parameter_BEG = 2000,
  blue_design_elliptic_parameter_center = blue_design_elliptic_parameter_BEG,
  blue_design_elliptic_parameter_width,
  blue_design_elliptic_parameter_height,
  blue_design_elliptic_parameter_rotation,
  blue_design_elliptic_parameter_start_angle,
  blue_design_elliptic_parameter_end_angle,
  blue_design_elliptic_parameter_defaults_xml,
  blue_design_elliptic_parameter_END
} blue_design_elliptic_parameter_t;

design_elliptic_s *blue_design_elliptic_parameter_handler(int argc,
                                                          char** argv,
                                                          design_elliptic_s *e);
int blue_design_elliptic_check(design_elliptic_s *e);
void blue_design_elliptic_check_error(void);
unsigned char blue_design_elliptic_get_change(
                blue_design_elliptic_parameter_t p);
void blue_design_elliptic_set_change(blue_design_elliptic_parameter_t p);
void blue_design_elliptic_unset_changes(void);

#endif // BLUE_DESIGN_ELLIPTIC_PARMS_H
