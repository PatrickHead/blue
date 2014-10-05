#ifndef DESIGN_VISIBILITY_TYPE_H
#define DESIGN_VISIBILITY_TYPE_H

typedef enum
{
  design_visibility_type_visible = 0,
  design_visibility_type_hidden
} design_visibility_t;

design_visibility_t str2design_visibility_type(char* s);
const char* design_visibility_type2str(design_visibility_t t);

#endif // DESIGN_VISIBILITY_TYPE_H
