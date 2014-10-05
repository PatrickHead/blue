#ifndef BLUE_DESIGN_LINE_PARMS_H
#define BLUE_DESIGN_LINE_PARMS_H

#include "design-line.h"

typedef enum
{
  blue_design_line_parameter_BEG = 2000,
  blue_design_line_parameter_start = blue_design_line_parameter_BEG,
  blue_design_line_parameter_end,
  blue_design_line_parameter_defaults_xml,
  blue_design_line_parameter_END
} blue_design_line_parameter_t;

design_line_s *blue_design_line_parameter_handler(int argc,
                                                  char** argv,
                                                  design_line_s *l);
int blue_design_line_check(design_line_s *l);
void blue_design_line_check_error(void);
unsigned char blue_design_line_get_change(blue_design_line_parameter_t p);
void blue_design_line_set_change(blue_design_line_parameter_t p);
void blue_design_line_unset_changes(void);

#endif // BLUE_DESIGN_LINE_PARMS_H
