#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "reference.h"

#include "design-line.h"

design_line_s *design_line_create(void)
{
  design_line_s *line;

  line = (design_line_s *)malloc(sizeof(design_line_s));
  memset(line, 0, sizeof(design_line_s));

  line->start = vertex_create();
  if (line->start) vertex_set(line->start, "start", 0.0, 0.0, 0.0);

  line->end = vertex_create();
  if (line->end) vertex_set(line->end, "end", 0.0, 0.0, 0.0);

  return line;
}

void design_line_destroy(design_line_s *l)
{
  assert(l);
  if (l->start) vertex_destroy(l->start);
  if (l->end) vertex_destroy(l->end);
  free(l);
}

design_line_s *design_line_copy(design_line_s *l)
{
  design_line_s *nl;

  assert(l);

  nl = design_line_create();
  memcpy(nl, l, sizeof(design_line_s));

  if (l->start) nl->start = vertex_copy(l->start);
  if (l->end) nl->end = vertex_copy(l->end);

  return nl;
}

void design_line_set(design_line_s *l,
                     vertex_s *start,
                     vertex_s *end)
{
  assert(l);
  assert(start);
  assert(end);

  design_line_set_start(l, start);
  design_line_set_end(l, end);
}

void design_line_get(design_line_s *l,
                     vertex_s **start,
                     vertex_s **end)
{
  assert(l);
  assert(start);
  assert(end);

  *start = design_line_get_start(l);
  *end = design_line_get_end(l);
}

void design_line_set_start(design_line_s *l, vertex_s *start)
{
  assert(l);
  assert(start);
  if (l->start) vertex_destroy(l->start);
  l->start = start;
  vertex_set_tag(l->start, "start");
}

vertex_s *design_line_get_start(design_line_s *l)
{
  assert(l);
  return l->start;
}

void design_line_set_end(design_line_s *l, vertex_s *end)
{
  assert(l);
  assert(end);
  if (l->end) vertex_destroy(l->end);
  l->end = end;
  vertex_set_tag(l->end, "end");
}

vertex_s *design_line_get_end(design_line_s *l)
{
  assert(l);
  return l->end;
}

