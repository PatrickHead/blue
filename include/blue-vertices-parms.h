#ifndef BLUE_VERTICES_PARMS_H
#define BLUE_VERTICES_PARMS_H

#include "vertices.h"

typedef enum
{
  blue_vertices_parameter_BEG = 2000,
  blue_vertices_parameter_vertex_xml,
  blue_vertices_parameter_END
} blue_vertices_parameter_t;

vertices_s *blue_vertices_parameter_handler(int argc,
                                            char** argv,
                                            vertices_s *vs);
int blue_vertices_check(vertices_s *vs);
void blue_vertices_check_error(void);
unsigned char blue_vertices_get_change(blue_vertices_parameter_t p);
void blue_vertices_set_change(blue_vertices_parameter_t p);
void blue_vertices_unset_changes(void);

#endif // BLUE_VERTICES_PARMS_H
