#ifndef BLUE_DESIGN_DIMENSION_PARMS_H
#define BLUE_DESIGN_DIMENSION_PARMS_H

#include "design-dimension.h"

typedef enum
{
  blue_design_dimension_parameter_BEG = 2000,
  blue_design_dimension_parameter_text_size = blue_design_dimension_parameter_BEG,
  blue_design_dimension_parameter_text_location,
  blue_design_dimension_parameter_precision,
  blue_design_dimension_parameter_angular_xml,
  blue_design_dimension_parameter_linear_xml,
  blue_design_dimension_parameter_radial_xml,
  blue_design_dimension_parameter_defaults_xml,
  blue_design_dimension_parameter_END
} blue_design_dimension_parameter_t;

design_dimension_s *blue_design_dimension_parameter_handler(int argc,
                                                            char** argv,
                                                          design_dimension_s *d);
int blue_design_dimension_check(design_dimension_s *d);
void blue_design_dimension_check_error(void);
unsigned char blue_design_dimension_get_change(
                blue_design_dimension_parameter_t p);
void blue_design_dimension_set_change(blue_design_dimension_parameter_t p);
void blue_design_dimension_unset_changes(void);

#endif // BLUE_DESIGN_DIMENSION_PARMS_H
