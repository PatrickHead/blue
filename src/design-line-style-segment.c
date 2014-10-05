#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "design-line-style-segment.h"

design_line_style_segment_s *design_line_style_segment_create(void)
{
  design_line_style_segment_s *line_style_segment;

  line_style_segment =
    (design_line_style_segment_s *)malloc(sizeof(design_line_style_segment_s));
  memset(line_style_segment, 0, sizeof(design_line_style_segment_s));

  return line_style_segment;
}

void design_line_style_segment_destroy_void(void *v)
{
  assert(v);
  design_line_style_segment_destroy((design_line_style_segment_s *)v);
}

void design_line_style_segment_destroy(design_line_style_segment_s *lss)
{
  assert(lss);
  free(lss);
}

design_line_style_segment_s *design_line_style_segment_copy(
  design_line_style_segment_s *lss)
{
  design_line_style_segment_s *nlss;

  assert(lss);

  nlss = design_line_style_segment_create();
  memcpy(nlss, lss, sizeof(design_line_style_segment_s));

  return nlss;
}

void design_line_style_segment_set(design_line_style_segment_s *lss,
                      double length)
{
  assert(lss);

  design_line_style_segment_set_length(lss, length);
}

void design_line_style_segment_get(design_line_style_segment_s *lss,
                      double *length)
{
  assert(lss);
  assert(length);

  *length = design_line_style_segment_get_length(lss);
}

void design_line_style_segment_set_length(design_line_style_segment_s *lss,
                                          double length)
{
  assert(lss);
  lss->length = length;
}

double design_line_style_segment_get_length(design_line_style_segment_s *lss)
{
  assert(lss);
  return lss->length;
}

