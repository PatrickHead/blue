#ifndef BLUE_DESIGN_PARMS_H
#define BLUE_DESIGN_PARMS_H

#include "design.h"

typedef enum
{
  blue_design_parameter_BEG = 2000,
  blue_design_parameter_defaults_xml,
  blue_design_parameter_line_styles_xml,
  blue_design_parameter_fill_styles_xml,
  blue_design_parameter_layers_xml,
  blue_design_parameter_END
} blue_design_parameter_t;

design_s *blue_design_parameter_handler(int argc, char** argv, design_s *d);
int blue_design_check(design_s *d);
void blue_design_check_error(void);
unsigned char blue_design_get_change(blue_design_parameter_t p);
void blue_design_set_change(blue_design_parameter_t p);
void blue_design_unset_changes(void);

#endif // BLUE_DESIGN_PARMS_H
