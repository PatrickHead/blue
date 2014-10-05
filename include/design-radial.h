#ifndef DESIGN_RADIAL_H
#define DESIGN_RADIAL_H

#include "vertex.h"

#include "design-radial-type.h"

typedef struct
{
  design_radial_t type;
  vertex_s *center; // center point of elliptic arc
  double major;  // major radius of elliptic arc, or only radius for circular arc
  double minor;  // minor radius of elliptic arc
  double angle;  // angle of leader, absolute in degrees
  double leader; // length of leader
} design_radial_s;

design_radial_s *design_radial_create(void);
void design_radial_destroy(design_radial_s *r);
design_radial_s *design_radial_copy(design_radial_s *r);

void design_radial_set(design_radial_s *r,
                       design_radial_t type,
                       vertex_s *center,
                       double major,
                       double minor,
                       double angle,
                       double leader);
void design_radial_get(design_radial_s *r,
                       design_radial_t *type,
                       vertex_s **center,
                       double *major,
                       double *minor,
                       double *angle,
                       double *leader);

void design_radial_set_type(design_radial_s *r, design_radial_t type); 
design_radial_t design_radial_get_type(design_radial_s *r);
void design_radial_set_center(design_radial_s *r, vertex_s *center); 
vertex_s *design_radial_get_center(design_radial_s *r);
void design_radial_set_major(design_radial_s *r, double major); 
double design_radial_get_major(design_radial_s *r);
void design_radial_set_minor(design_radial_s *r, double minor); 
double design_radial_get_minor(design_radial_s *r);
void design_radial_set_angle(design_radial_s *r, double angle); 
double design_radial_get_angle(design_radial_s *r);
void design_radial_set_leader(design_radial_s *r, double leader); 
double design_radial_get_leader(design_radial_s *r);

#endif // DESIGN_RADIAL_H
