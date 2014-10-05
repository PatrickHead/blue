#ifndef DESIGN_TEXT_TYPE
#define DESIGN_TEXT_TYPE

typedef enum
{
  design_text_type_drawing,
  design_text_type_annotation
} design_text_t;

design_text_t str2design_text_type(char* s);
const char* design_text_type2str(design_text_t t);

#endif // DESIGN_TEXT_TYPE
