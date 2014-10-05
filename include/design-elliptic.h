#ifndef DESIGN_ELLIPTIC_H
#define DESIGN_ELLIPTIC_H

#include "vertex.h"

typedef struct
{
  vertex_s *center;
  double width;
  double height;
  double rotation;
  double start_angle;
  double end_angle;
} design_elliptic_s;

design_elliptic_s *design_elliptic_create(void);
void design_elliptic_destroy(design_elliptic_s *e);
design_elliptic_s *design_elliptic_copy(design_elliptic_s *e);

void design_elliptic_set(design_elliptic_s *e,
                         vertex_s *center,
                         double width,
                         double height,
                         double rotation,
                         double start_angle,
                         double end_angle);
void design_elliptic_get(design_elliptic_s *e,
                         vertex_s **center,
                         double *width,
                         double *height,
                         double *rotation,
                         double *start_angle,
                         double *end_angle);

void design_elliptic_set_center(design_elliptic_s *e, vertex_s *center); 
vertex_s *design_elliptic_get_center(design_elliptic_s *e);

void design_elliptic_set_width(design_elliptic_s *e, double width); 
double design_elliptic_get_width(design_elliptic_s *e);

void design_elliptic_set_height(design_elliptic_s *e, double height); 
double design_elliptic_get_height(design_elliptic_s *e);

void design_elliptic_set_rotation(design_elliptic_s *e, double rotation); 
double design_elliptic_get_rotation(design_elliptic_s *e);

void design_elliptic_set_start_angle(design_elliptic_s *e, double start_angle); 
double design_elliptic_get_start_angle(design_elliptic_s *e);

void design_elliptic_set_end_angle(design_elliptic_s *e, double end_angle); 
double design_elliptic_get_end_angle(design_elliptic_s *e);

#endif // DESIGN_ELLIPTIC_H
