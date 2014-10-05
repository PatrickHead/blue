#ifndef BLUE_DESIGN_ELEMENT_PARMS_H
#define BLUE_DESIGN_ELEMENT_PARMS_H

#include "design-element.h"

typedef enum
{
  blue_design_element_parameter_BEG = 2000,
  blue_design_element_parameter_id,
  blue_design_element_parameter_units,
  blue_design_element_parameter_line_weight,
  blue_design_element_parameter_line_style,
  blue_design_element_parameter_fill_style,
  blue_design_element_parameter_color_xml,
  blue_design_element_parameter_dimension_xml,
  blue_design_element_parameter_elliptic_xml,
  blue_design_element_parameter_fill_xml,
  blue_design_element_parameter_line_xml,
  blue_design_element_parameter_point_xml,
  blue_design_element_parameter_polyline_xml,
  blue_design_element_parameter_spline_xml,
  blue_design_element_parameter_text_xml,
  blue_design_element_parameter_tolerance_xml,
  blue_design_element_parameter_defaults_xml,
  blue_design_element_parameter_END
} blue_design_element_parameter_t;

design_element_s *blue_design_element_parameter_handler(int argc,
                                                        char** argv,
                                                        design_element_s *e);
int blue_design_element_check(design_element_s *e);
void blue_design_element_check_error(void);
unsigned char blue_design_element_get_change(blue_design_element_parameter_t p);
void blue_design_element_set_change(blue_design_element_parameter_t p);
void blue_design_element_unset_changes(void);

#endif // BLUE_DESIGN_ELEMENT_PARMS_H
