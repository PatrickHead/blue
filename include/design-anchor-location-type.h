#ifndef DESIGN_ANCHOR_LOCATION_TYPE_H
#define DESIGN_ANCHOR_LOCATION_TYPE_H

typedef enum
{
  design_anchor_location_type_upper_left,
  design_anchor_location_type_upper_right,
  design_anchor_location_type_center,
  design_anchor_location_type_lower_left,
  design_anchor_location_type_lower_right
} design_anchor_location_t;

design_anchor_location_t str2design_anchor_location_type(char* s);
const char* design_anchor_location_type2str(design_anchor_location_t t);

#endif // DESIGN_ANCHOR_LOCATION_TYPE_H
