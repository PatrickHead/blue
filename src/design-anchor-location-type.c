#include <string.h>
#include <assert.h>

#include "design-anchor-location-type.h"

design_anchor_location_t str2design_anchor_location_type(char* s)
{
  assert(s);

  if (!strcmp(s, "upper-left")) return design_anchor_location_type_upper_left;
  if (!strcmp(s, "upper-right")) return design_anchor_location_type_upper_right;
  if (!strcmp(s, "center")) return design_anchor_location_type_center;
  if (!strcmp(s, "lower-left")) return design_anchor_location_type_lower_left;
  if (!strcmp(s, "lower-right")) return design_anchor_location_type_lower_right;

  return design_anchor_location_type_center;
}

const char* design_anchor_location_type2str(design_anchor_location_t t)
{
  switch (t)
  {
    case design_anchor_location_type_upper_left: return "upper-left";
    case design_anchor_location_type_upper_right: return "upper-right";
    case design_anchor_location_type_center: return "center";
    case design_anchor_location_type_lower_left: return "lower-left";
    case design_anchor_location_type_lower_right: return "lower-right";
  }

  return "UNKNOWN";
}

