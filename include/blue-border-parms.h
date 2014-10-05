#ifndef BLUE_BORDER_PARMS_H
#define BLUE_BORDER_PARMS_H

#include "border.h"

typedef enum
{
  blue_border_parameter_BEG = 2000,
  blue_border_parameter_units = blue_border_parameter_BEG,
  blue_border_parameter_line_width,
  blue_border_parameter_background_color_xml,
  blue_border_parameter_line_color_xml,
  blue_border_parameter_margins_xml,
  blue_border_parameter_END
} blue_border_parameter_t;

border_s *blue_border_parameter_handler(int argc, char** argv, border_s *b);
int blue_border_check(border_s *b);
void blue_border_check_error(void);
unsigned char blue_border_get_change(blue_border_parameter_t p);
void blue_border_set_change(blue_border_parameter_t p);
void blue_border_unset_changes(void);

#endif // BLUE_BORDER_PARMS_H
