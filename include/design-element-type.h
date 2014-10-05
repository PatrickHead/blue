#ifndef DESIGN_ELEMENT_TYPE_H
#define DESIGN_ELEMENT_TYPE_H

typedef enum
{
  design_element_type_BEG = 0,
  design_element_type_dimension = 0,
  design_element_type_elliptic,
  design_element_type_line,
  design_element_type_point,
  design_element_type_polyline,
  design_element_type_spline,
  design_element_type_text,
  design_element_type_tolerance,
  design_element_type_END
} design_element_t;

design_element_t str2design_element_type(char* s);
const char* design_element_type2str(design_element_t t);

#endif // DESIGN_ELEMENT_TYPE_H
