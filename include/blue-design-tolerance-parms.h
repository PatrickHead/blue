#ifndef BLUE_DESIGN_TOLERANCE_PARMS_H
#define BLUE_DESIGN_TOLERANCE_PARMS_H

#include "design-tolerance.h"

typedef enum
{
  blue_design_tolerance_parameter_BEG = 2000,
  blue_design_tolerance_parameter_location = blue_design_tolerance_parameter_BEG,
  blue_design_tolerance_parameter_text_size,
  blue_design_tolerance_parameter_plus,
  blue_design_tolerance_parameter_minus,
  blue_design_tolerance_parameter_precision,
  blue_design_tolerance_parameter_defaults_xml,
  blue_design_tolerance_parameter_END
} blue_design_tolerance_parameter_t;

design_tolerance_s *blue_design_tolerance_parameter_handler(int argc,
                                                          char** argv,
                                                          design_tolerance_s *t);
int blue_design_tolerance_check(design_tolerance_s *t);
void blue_design_tolerance_check_error(void);
unsigned char blue_design_tolerance_get_change(
                blue_design_tolerance_parameter_t p);
void blue_design_tolerance_set_change(blue_design_tolerance_parameter_t p);
void blue_design_tolerance_unset_changes(void);

#endif // BLUE_DESIGN_TOLERANCE_PARMS_H
