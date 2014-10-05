#ifndef BLUE_DESIGN_LINE_STYLES_PARMS_H
#define BLUE_DESIGN_LINE_STYLES_PARMS_H

#include "design-line-styles.h"

typedef enum
{
  blue_design_line_styles_parameter_BEG = 2000,
  blue_design_line_styles_parameter_line_style_xml,
  blue_design_line_styles_parameter_END
} blue_design_line_styles_parameter_t;

design_line_styles_s *blue_design_line_styles_parameter_handler(int argc,
                                                                char** argv,
                                                       design_line_styles_s *lss);
int blue_design_line_styles_check(design_line_styles_s *lss);
void blue_design_line_styles_check_error(void);
unsigned char blue_design_line_styles_get_change(
  blue_design_line_styles_parameter_t p);
void blue_design_line_styles_set_change(
  blue_design_line_styles_parameter_t p);
void blue_design_line_styles_unset_changes(void);

#endif // BLUE_DESIGN_LINE_STYLES_PARMS_H
