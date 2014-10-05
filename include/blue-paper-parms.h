#ifndef BLUE_PAPER_PARMS_H
#define BLUE_PAPER_PARMS_H

#include "paper.h"

typedef enum
{
  blue_paper_parameter_BEG = 1000,
  blue_paper_parameter_units = blue_paper_parameter_BEG,
  blue_paper_parameter_size,
  blue_paper_parameter_orientation,
  blue_paper_parameter_margins_xml,
  blue_paper_parameter_width,
  blue_paper_parameter_height,
  blue_paper_parameter_color_xml,
  blue_paper_parameter_END
} blue_paper_parameter_t;

paper_s *blue_paper_parameter_handler(int argc, char** argv, paper_s *p);
int blue_paper_check(paper_s *p);
void blue_paper_check_error(void);
unsigned char blue_paper_get_change(blue_paper_parameter_t p);
void blue_paper_set_change(blue_paper_parameter_t p);
void blue_paper_unset_changes(void);

#endif // BLUE_PAPER_PARMS_H
