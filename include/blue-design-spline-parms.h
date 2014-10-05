#ifndef BLUE_DESIGN_SPLINE_PARMS_H
#define BLUE_DESIGN_SPLINE_PARMS_H

#include "design-spline.h"

typedef enum
{
  blue_design_spline_parameter_BEG = 2000,
  blue_design_spline_parameter_vertices_xml,
  blue_design_spline_parameter_defaults_xml,
  blue_design_spline_parameter_END
} blue_design_spline_parameter_t;

design_spline_s *blue_design_spline_parameter_handler(int argc,
                                                      char** argv,
                                                      design_spline_s *s);
int blue_design_spline_check(design_spline_s *s);
void blue_design_spline_check_error(void);
unsigned char blue_design_spline_get_change(blue_design_spline_parameter_t p);
void blue_design_spline_set_change(blue_design_spline_parameter_t p);
void blue_design_spline_unset_changes(void);

#endif // BLUE_DESIGN_SPLINE_PARMS_H
