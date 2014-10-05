#ifndef DESIGN_ANGULAR_H
#define DESIGN_ANGULAR_H

#include "vertex.h"

typedef struct
{
  double angle; // 0 is automatic
  vertex_s *alpha; // angular measurement is based at the intersection of
  vertex_s *beta;  //   line segments alpha.beta and alpha.gamma
  vertex_s *gamma;
  double gap;
  double extension;
} design_angular_s;

design_angular_s *design_angular_create(void);
void design_angular_destroy(design_angular_s *a);
design_angular_s *design_angular_copy(design_angular_s *a);

void design_angular_set(design_angular_s *a,
                        double angle,
                        vertex_s *alpha,
                        vertex_s *beta,
                        vertex_s *gamma,
                        double gap,
                        double extension);
void design_angular_get(design_angular_s *a,
                        double *angle,
                        vertex_s **alpha,
                        vertex_s **beta,
                        vertex_s **gamma,
                        double *gap,
                        double *extension);

void design_angular_set_angle(design_angular_s *a, double angle); 
double design_angular_get_angle(design_angular_s *a);
void design_angular_set_alpha(design_angular_s *a, vertex_s *alpha); 
vertex_s *design_angular_get_alpha(design_angular_s *a);
void design_angular_set_beta(design_angular_s *a, vertex_s *beta); 
vertex_s *design_angular_get_beta(design_angular_s *a);
void design_angular_set_gamma(design_angular_s *a, vertex_s *gamma); 
vertex_s *design_angular_get_gamma(design_angular_s *a);
void design_angular_set_gap(design_angular_s *a, double gap); 
double design_angular_get_gap(design_angular_s *a);
void design_angular_set_extension(design_angular_s *a, double extension); 
double design_angular_get_extension(design_angular_s *a);

#endif // DESIGN_ANGULAR_H
