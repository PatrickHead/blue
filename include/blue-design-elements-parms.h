#ifndef BLUE_DESIGN_ELEMENTS_PARMS_H
#define BLUE_DESIGN_ELEMENTS_PARMS_H

#include "design-elements.h"

typedef enum
{
  blue_design_elements_parameter_BEG = 2000,
  blue_design_elements_parameter_element_xml,
  blue_design_elements_parameter_END
} blue_design_elements_parameter_t;

design_elements_s *blue_design_elements_parameter_handler(int argc,
                                                          char** argv,
                                                          design_elements_s *es);
int blue_design_elements_check(design_elements_s *es);
void blue_design_elements_check_error(void);
unsigned char blue_design_elements_get_change(
  blue_design_elements_parameter_t p);
void blue_design_elements_set_change(blue_design_elements_parameter_t p);
void blue_design_elements_unset_changes(void);

#endif // BLUE_DESIGN_ELEMENTS_PARMS_H
