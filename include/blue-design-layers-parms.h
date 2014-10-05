#ifndef BLUE_DESIGN_LAYERS_PARMS_H
#define BLUE_DESIGN_LAYERS_PARMS_H

#include "design-layers.h"

typedef enum
{
  blue_design_layers_parameter_BEG = 2000,
  blue_design_layers_parameter_layer_xml,
  blue_design_layers_parameter_END
} blue_design_layers_parameter_t;

design_layers_s *blue_design_layers_parameter_handler(int argc,
                                                      char** argv,
                                                      design_layers_s *ls);
int blue_design_layers_check(design_layers_s *ls);
void blue_design_layers_check_error(void);
unsigned char blue_design_layers_get_change(blue_design_layers_parameter_t p);
void blue_design_layers_set_change(blue_design_layers_parameter_t p);
void blue_design_layers_unset_changes(void);

#endif // BLUE_DESIGN_LAYERS_PARMS_H
