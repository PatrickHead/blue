#ifndef DESIGN_RADIAL_TYPE_H
#define DESIGN_RADIAL_TYPE_H

typedef enum
{
  design_radial_type_radius,
  design_radial_type_diameter
} design_radial_t;

design_radial_t str2design_radial_type(char* s);
const char* design_radial_type2str(design_radial_t t);

#endif // DESIGN_RADIAL_TYPE_H
