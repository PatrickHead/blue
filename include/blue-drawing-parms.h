#ifndef BLUE_DRAWING_PARMS_H
#define BLUE_DRAWING_PARMS_H

#include "drawing.h"

typedef enum
{
  blue_drawing_parameter_BEG = 2000,
  blue_drawing_parameter_paper_xml,
  blue_drawing_parameter_border_xml,
  blue_drawing_parameter_title_block_xml,
  blue_drawing_parameter_design_xml,
  blue_drawing_parameter_END
} blue_drawing_parameter_t;

drawing_s *blue_drawing_parameter_handler(int argc, char** argv, drawing_s *d);
int blue_drawing_check(drawing_s *d);
void blue_drawing_check_error(void);
unsigned char blue_drawing_get_change(blue_drawing_parameter_t p);
void blue_drawing_set_change(blue_drawing_parameter_t p);
void blue_drawing_unset_changes(void);

#endif // BLUE_DRAWING_PARMS_H
