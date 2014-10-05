#include <string.h>
#include <assert.h>

#include "design-dimension-type.h"

design_dimension_t str2design_dimension_type(char* s)
{
  assert(s);

  if (!strcmp(s, "linear")) return design_dimension_type_linear;
  if (!strcmp(s, "angular")) return design_dimension_type_angular;
  if (!strcmp(s, "radial")) return design_dimension_type_radial;

  return design_dimension_type_linear;
}

const char* design_dimension_type2str(design_dimension_t t)
{
  switch (t)
  {
    case design_dimension_type_linear: return "linear";
    case design_dimension_type_angular: return "angular";
    case design_dimension_type_radial: return "radial";
    default: break;
  }

  return "UNKNOWN";
}

