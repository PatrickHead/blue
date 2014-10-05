#ifndef BLUE_DESIGN_TEXT_PARMS_H
#define BLUE_DESIGN_TEXT_PARMS_H

#include "design-text.h"

typedef enum
{
  blue_design_text_parameter_BEG = 2000,
  blue_design_text_parameter__type = blue_design_text_parameter_BEG,
  blue_design_text_parameter_location,
  blue_design_text_parameter_rotation,
  blue_design_text_parameter_anchor_point,
  blue_design_text_parameter_size,
  blue_design_text_parameter_text,
  blue_design_text_parameter_defaults_xml,
  blue_design_text_parameter_END
} blue_design_text_parameter_t;

design_text_s *blue_design_text_parameter_handler(int argc,
                                                  char** argv,
                                                  design_text_s *t);
int blue_design_text_check(design_text_s *t);
void blue_design_text_check_error(void);
unsigned char blue_design_text_get_change(blue_design_text_parameter_t p);
void blue_design_text_set_change(blue_design_text_parameter_t p);
void blue_design_text_unset_changes(void);

#endif // BLUE_DESIGN_TEXT_PARMS_H
