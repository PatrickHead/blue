#include <string.h>
#include <assert.h>

#include "design-element-type.h"

design_element_t str2design_element_type(char* s)
{
  assert(s);

  if (!strcmp(s, "dimension")) return design_element_type_dimension;
  if (!strcmp(s, "elliptic")) return design_element_type_elliptic;
  if (!strcmp(s, "line")) return design_element_type_line;
  if (!strcmp(s, "point")) return design_element_type_point;
  if (!strcmp(s, "polyline")) return design_element_type_polyline;
  if (!strcmp(s, "spline")) return design_element_type_spline;
  if (!strcmp(s, "text")) return design_element_type_text;
  if (!strcmp(s, "tolerance")) return design_element_type_tolerance;

  return design_element_type_END;
}

const char* design_element_type2str(design_element_t t)
{
  switch (t)
  {
    case design_element_type_dimension: return "dimension";
    case design_element_type_elliptic: return "elliptic";
    case design_element_type_line: return "line";
    case design_element_type_point: return "point";
    case design_element_type_polyline: return "polyline";
    case design_element_type_spline: return "spline";
    case design_element_type_text: return "text";
    case design_element_type_tolerance: return "tolerance";
    case design_element_type_END: return "UNKNOWN";
  }

  return "UNKNOWN";
}

