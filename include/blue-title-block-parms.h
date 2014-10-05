#ifndef BLUE_TITLE_BLOCK_PARMS_H
#define BLUE_TITLE_BLOCK_PARMS_H

#include "title-block.h"

typedef enum
{
  blue_title_block_parameter_BEG = 2000,
  blue_title_block_parameter_title = blue_title_block_parameter_BEG,
  blue_title_block_parameter_part,
  blue_title_block_parameter_provider,
  blue_title_block_parameter_consumer,
  blue_title_block_parameter_revision,
  blue_title_block_parameter_reference,
  blue_title_block_parameter_page,
  blue_title_block_parameter_of,
  blue_title_block_parameter_time,
  blue_title_block_parameter_background_color_xml,
  blue_title_block_parameter_line_color_xml,
  blue_title_block_parameter_text_color_xml,
  blue_title_block_parameter_END
} blue_title_block_parameter_t;

title_block_s *blue_title_block_parameter_handler(int argc,
                                                  char** argv,
                                                  title_block_s *tb);
int blue_title_block_check(title_block_s *tb);
void blue_title_block_check_error(void);
unsigned char blue_title_block_get_change(blue_title_block_parameter_t p);
void blue_title_block_set_change(blue_title_block_parameter_t p);
void blue_title_block_unset_changes(void);

#endif // BLUE_TITLE_BLOCK_PARMS_H
