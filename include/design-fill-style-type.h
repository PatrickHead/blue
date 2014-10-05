#ifndef DESIGN_FILL_STYLE_TYPE
#define DESIGN_FILL_STYLE_TYPE

typedef enum
{
  design_fill_style_type_line,
  design_fill_style_type_hatch,
  design_fill_style_type_stipple,
  design_fill_style_type_source_only
} design_fill_style_t;

design_fill_style_t str2design_fill_style_type(char* s);
const char* design_fill_style_type2str(design_fill_style_t t);

#endif // DESIGN_FILL_STYLE_TYPE
