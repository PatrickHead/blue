#ifndef BLUE_DESIGN_POLYLINE_PARMS_H
#define BLUE_DESIGN_POLYLINE_PARMS_H

#include "design-polyline.h"

typedef enum
{
  blue_design_polyline_parameter_BEG = 2000,
  blue_design_polyline_parameter_vertices_xml,
  blue_design_polyline_parameter_defaults_xml,
  blue_design_polyline_parameter_END
} blue_design_polyline_parameter_t;

design_polyline_s *blue_design_polyline_parameter_handler(int argc,
                                                          char** argv,
                                                          design_polyline_s *pl);
int blue_design_polyline_check(design_polyline_s *pl);
void blue_design_polyline_check_error(void);
unsigned char blue_design_polyline_get_change(
  blue_design_polyline_parameter_t p);
void blue_design_polyline_set_change(blue_design_polyline_parameter_t p);
void blue_design_polyline_unset_changes(void);

#endif // BLUE_DESIGN_POLYLINE_PARMS_H
