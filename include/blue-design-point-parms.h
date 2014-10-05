#ifndef BLUE_DESIGN_POINT_PARMS_H
#define BLUE_DESIGN_POINT_PARMS_H

#include "design-point.h"

typedef enum
{
  blue_design_point_parameter_BEG = 2000,
  blue_design_point_parameter_location = blue_design_point_parameter_BEG,
  blue_design_point_parameter_defaults_xml,
  blue_design_point_parameter_END
} blue_design_point_parameter_t;

design_point_s *blue_design_point_parameter_handler(int argc,
                                                    char** argv,
                                                    design_point_s *p);
int blue_design_point_check(design_point_s *p);
void blue_design_point_check_error(void);
unsigned char blue_design_point_get_change(blue_design_point_parameter_t p);
void blue_design_point_set_change(blue_design_point_parameter_t p);
void blue_design_point_unset_changes(void);

#endif // BLUE_DESIGN_POINT_PARMS_H
