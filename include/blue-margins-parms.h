#ifndef BLUE_MARGINS_PARMS_H
#define BLUE_MARGINS_PARMS_H

#include "margins.h"

typedef enum
{
  blue_margins_parameter_BEG = 2000,
  blue_margins_parameter_units = blue_margins_parameter_BEG,
  blue_margins_parameter_top,
  blue_margins_parameter_bottom,
  blue_margins_parameter_left,
  blue_margins_parameter_right,
  blue_margins_parameter_END
} blue_margins_parameter_t;

margins_s *blue_margins_parameter_handler(int argc, char** argv, margins_s *m);
int blue_margins_check(margins_s *m);
void blue_margins_check_error(void);
unsigned char blue_margins_get_change(blue_margins_parameter_t p);
void blue_margins_set_change(blue_margins_parameter_t p);
void blue_margins_unset_changes(void);

#endif // BLUE_MARGINS_PARMS_H
