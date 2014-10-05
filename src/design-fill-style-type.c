#include <string.h>
#include <assert.h>

#include "design-fill-style-type.h"

design_fill_style_t str2design_fill_style_type(char* s)
{
  assert(s);

  if (!strcmp(s, "line")) return design_fill_style_type_line;
  if (!strcmp(s, "hatch")) return design_fill_style_type_hatch;
  if (!strcmp(s, "stipple")) return design_fill_style_type_stipple;
  if (!strcmp(s, "source-only")) return design_fill_style_type_source_only;

  return design_fill_style_type_line;
}

const char* design_fill_style_type2str(design_fill_style_t t)
{
  switch (t)
  {
    case design_fill_style_type_line: return "line";
    case design_fill_style_type_hatch: return "hatch";
    case design_fill_style_type_stipple: return "stipple";
    case design_fill_style_type_source_only: return "source-only";
  }

  return "UNKNOWN";
}

