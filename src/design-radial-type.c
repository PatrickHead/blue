#include <string.h>
#include <assert.h>

#include "design-radial-type.h"

design_radial_t str2design_radial_type(char* s)
{
  assert(s);

  if (!strcmp(s, "radius")) return design_radial_type_radius;
  if (!strcmp(s, "diameter")) return design_radial_type_diameter;

  return design_radial_type_radius;
}

const char* design_radial_type2str(design_radial_t t)
{
  switch (t)
  {
    case design_radial_type_radius: return "radius";
    case design_radial_type_diameter: return "diameter";
  }

  return "UNKNOWN";
}

