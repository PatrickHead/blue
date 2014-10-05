#include <string.h>
#include <assert.h>

#include "design-text-type.h"

design_text_t str2design_text_type(char* s)
{
  assert(s);

  if (!strcmp(s, "drawing")) return design_text_type_drawing;
  if (!strcmp(s, "annotation")) return design_text_type_annotation;

  return design_text_type_drawing;
}

const char* design_text_type2str(design_text_t t)
{
  switch (t)
  {
    case design_text_type_drawing: return "drawing";
    case design_text_type_annotation: return "annotation";
  }

  return "UNKNOWN";
}

