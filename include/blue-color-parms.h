#ifndef BLUE_COLOR_PARMS_H
#define BLUE_COLOR_PARMS_H

#include "color.h"

typedef enum
{
  blue_color_parameter_BEG = 2000,
  blue_color_parameter_tag,
  blue_color_parameter_r,
  blue_color_parameter_g,
  blue_color_parameter_b,
  blue_color_parameter_a,
  blue_color_parameter_END
} blue_color_parameter_t;

color_s *blue_color_parameter_handler(int argc, char** argv, color_s *color);
int blue_color_check(color_s *color);
void blue_color_check_error(void);
unsigned char blue_color_get_change(blue_color_parameter_t p);
void blue_color_set_change(blue_color_parameter_t p);
void blue_color_unset_changes(void);

#endif // BLUE_COLOR_PARMS_H
