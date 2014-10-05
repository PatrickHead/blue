#include <string.h>
#include <assert.h>

#include "design-visibility-type.h"

design_visibility_t str2design_visibility_type(char* s)
{
  assert(s);

  if (!strcmp(s, "visible")) return design_visibility_type_visible;
  if (!strcmp(s, "hidden")) return design_visibility_type_hidden;

  return design_visibility_type_visible;
}

const char* design_visibility_type2str(design_visibility_t t)
{
  switch (t)
  {
    case design_visibility_type_visible: return "visible";
    case design_visibility_type_hidden: return "hidden";
  }

  return "visible";
}

