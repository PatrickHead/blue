#ifndef BLUE_DESIGN_LAYER_PARMS_H
#define BLUE_DESIGN_LAYER_PARMS_H

#include "design-layer.h"

typedef enum
{
  blue_design_layer_parameter_BEG = 2000,
  blue_design_layer_parameter_id,
  blue_design_layer_parameter_name,
  blue_design_layer_parameter_visibility,
  blue_design_layer_parameter_defaults_xml,
  blue_design_layer_parameter_elements_xml,
  blue_design_layer_parameter_END
} blue_design_layer_parameter_t;

design_layer_s *blue_design_layer_parameter_handler(int argc,
                                                    char** argv,
                                                    design_layer_s *l);
int blue_design_layer_check(design_layer_s *l);
void blue_design_layer_check_error(void);
unsigned char blue_design_layer_get_change(blue_design_layer_parameter_t p);
void blue_design_layer_set_change(blue_design_layer_parameter_t p);
void blue_design_layer_unset_changes(void);

#endif // BLUE_DESIGN_LAYER_PARMS_H
