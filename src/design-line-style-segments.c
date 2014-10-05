#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "design-line-style-segments.h"

design_line_style_segments_s *design_line_style_segments_create(void)
{
  design_line_style_segments_s *lsss;

  lsss =
    (design_line_style_segments_s *)malloc(sizeof(design_line_style_segments_s));
  memset(lsss, 0, sizeof(design_line_style_segments_s));

  lsss->line_style_segments = list_new();
  list_set_free(lsss->line_style_segments,
                design_line_style_segment_destroy_void);

  return lsss;
}

void design_line_style_segments_destroy(design_line_style_segments_s *lss)
{
  assert(lss);
  if (lss->line_style_segments) list_destroy(lss->line_style_segments);
  free(lss);
}

design_line_style_segments_s *design_line_style_segments_copy(
  design_line_style_segments_s *lsss)
{
  design_line_style_segments_s *nlsss;
  design_line_style_segment_s *lss;
  design_line_style_segment_s *nlss;

  assert(lsss);

  nlsss = design_line_style_segments_create();
  memcpy(nlsss, lsss, sizeof(design_line_style_segments_s));

  if (lsss->line_style_segments)
  {
    nlsss->line_style_segments = list_new();
    for (lss =
          (design_line_style_segment_s *)list_head(lsss->line_style_segments);
         lss;
         lss =
          (design_line_style_segment_s *)list_next(lsss->line_style_segments))
    {
      nlss = design_line_style_segment_copy(lss);
      list_insert(nlsss->line_style_segments, (void *)nlss, (void *)TAIL);
    }
  }

  return nlsss;
}

void design_line_style_segments_add_line_style_segment(
  design_line_style_segments_s *lsss,
  design_line_style_segment_s *lss)
{
  assert(lsss);
  assert(lss);
  list_insert(lsss->line_style_segments, lss, (void *)TAIL);
}

