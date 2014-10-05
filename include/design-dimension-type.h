#ifndef DESIGN_DIMENSION_TYPE_H
#define DESIGN_DIMENSION_TYPE_H

typedef enum
{
  design_dimension_type_BEG = 0,
  design_dimension_type_linear = 0,
  design_dimension_type_angular,
  design_dimension_type_radial,
  design_dimension_type_END,
} design_dimension_t;

design_dimension_t str2design_dimension_type(char* s);
const char* design_dimension_type2str(design_dimension_t t);

#endif // DESIGN_DIMENSION_TYPE_H
