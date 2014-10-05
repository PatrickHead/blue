#ifndef DESIGN_DIMENSION_H
#define DESIGN_DIMENSION_H

#include "vertex.h"

#include "design-dimension-type.h"
#include "design-linear.h"
#include "design-angular.h"
#include "design-radial.h"

typedef struct
{
  design_dimension_t type;
  double text_size;
  vertex_s *text_location;
  int precision;
  union
  {
    design_linear_s *linear;
    design_angular_s *angular;
    design_radial_s *radial;
  };
} design_dimension_s;

design_dimension_s *design_dimension_create(void);
void design_dimension_destroy(design_dimension_s *d);
design_dimension_s *design_dimension_copy(design_dimension_s *d);

void design_dimension_set(design_dimension_s *d,
                          design_dimension_t type,
                          double text_size,
                          vertex_s *text_location,
                          int precision,
                          void *data);
void design_dimension_get(design_dimension_s *d,
                          design_dimension_t *type,
                          double *text_size,
                          vertex_s **text_location,
                          int *precision,
                          void **data);

void design_dimension_set_type(design_dimension_s *d,
                               design_dimension_t type); 
design_dimension_t design_dimension_get_type(design_dimension_s *d);
void design_dimension_set_text_size(design_dimension_s *d, double text_size); 
double design_dimension_get_text_size(design_dimension_s *d);
void design_dimension_set_text_location(design_dimension_s *d,
                                        vertex_s *text_location); 
vertex_s *design_dimension_get_text_location(design_dimension_s *d);
void design_dimension_set_precision(design_dimension_s *d, int precision); 
int design_dimension_get_precision(design_dimension_s *d);
void design_dimension_set_linear(design_dimension_s *d, design_linear_s *linear); 
design_linear_s *design_dimension_get_linear(design_dimension_s *d);
void design_dimension_set_angular(design_dimension_s *d,
                                  design_angular_s *angular); 
design_angular_s *design_dimension_get_angular(design_dimension_s *d);
void design_dimension_set_radial(design_dimension_s *d, design_radial_s *radial); 
design_radial_s *design_dimension_get_radial(design_dimension_s *d);

#endif // DESIGN_DIMENSION_H
