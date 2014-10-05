#ifndef BLUE_VERTEX_PARMS_H
#define BLUE_VERTEX_PARMS_H

#include "vertex.h"

typedef enum
{
  blue_vertex_parameter_BEG = 2000,
  blue_vertex_parameter_tag,
  blue_vertex_parameter_x,
  blue_vertex_parameter_y,
  blue_vertex_parameter_z,
  blue_vertex_parameter_END
} blue_vertex_parameter_t;

vertex_s *blue_vertex_parameter_handler(int argc, char** argv, vertex_s *v);
int blue_vertex_check(vertex_s *v);
void blue_vertex_check_error(void);
unsigned char blue_vertex_get_change(blue_vertex_parameter_t p);
void blue_vertex_set_change(blue_vertex_parameter_t p);
void blue_vertex_unset_changes(void);

#endif // BLUE_VERTEX_PARMS_H
