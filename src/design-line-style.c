#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "design-line-style.h"

design_line_style_s *design_line_style_create(void)
{
  design_line_style_s *dls;

  dls = (design_line_style_s *)malloc(sizeof(design_line_style_s));
  memset(dls, 0, sizeof(design_line_style_s));

  dls->name = strdup("AUTO");
  dls->line_style_segments = design_line_style_segments_create();

  return dls;
}

void design_line_style_destroy_void(void *v)
{
  assert(v);
  design_line_style_destroy((design_line_style_s *)v);
}

void design_line_style_destroy(design_line_style_s *dls)
{
  assert(dls);

  if (dls->name) free(dls->name);
  if (dls->line_style_segments)
    design_line_style_segments_destroy(dls->line_style_segments);

  free(dls);
}

design_line_style_s *design_line_style_copy(design_line_style_s *dls)
{
  design_line_style_s *ndls;

  assert(dls);

  ndls = design_line_style_create();
  memcpy(ndls, dls, sizeof(design_line_style_s));

  if (dls->name) ndls->name = strdup(dls->name);
  if (dls->line_style_segments)
  {
    ndls->line_style_segments =
      design_line_style_segments_copy(dls->line_style_segments);
  }

  return ndls;
}

void design_line_style_set(design_line_style_s *dls,
                           char *name,
                           design_line_style_segments_s *line_style_segments)
{
  assert(dls);
  assert(name);
  assert(line_style_segments);

  design_line_style_set_name(dls, name);
  design_line_style_set_line_style_segments(dls, line_style_segments);
}

void design_line_style_get(design_line_style_s *dls,
                           char **name,
                           design_line_style_segments_s **line_style_segments)
{
  assert(dls);
  assert(name);
  assert(line_style_segments);

  *name = design_line_style_get_name(dls);
  *line_style_segments = design_line_style_get_line_style_segments(dls);
}

void design_line_style_set_name(design_line_style_s *dls, char *name)
{
  assert(dls);
  assert(name);

  if (dls->name) free(dls->name);
  dls->name = strdup(name);
}

char *design_line_style_get_name(design_line_style_s *dls)
{
  assert(dls);
  return dls->name;
}

void design_line_style_set_line_style_segments(design_line_style_s *dls,
                                               design_line_style_segments_s *lsss)
{
  assert(dls);
  assert(lsss);

  if (dls->line_style_segments)
    design_line_style_segments_destroy(dls->line_style_segments);
  dls->line_style_segments = lsss;
}

design_line_style_segments_s *design_line_style_get_line_style_segments(
  design_line_style_s *dls)
{
  assert(dls);
  return dls->line_style_segments;
}

void design_line_style_add_segment(design_line_style_s *dls,
                                   design_line_style_segment_s *lss)
{
  assert(dls);
  assert(lss);

  design_line_style_segments_add_line_style_segment(dls->line_style_segments,
                                                    lss);
}

