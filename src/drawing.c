#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "drawing.h"

drawing_s *drawing_create(void)
{
  drawing_s *d;
  d = (drawing_s *)malloc(sizeof(drawing_s));
  memset(d, 0, sizeof(drawing_s));
  return d;
}

void drawing_destroy(drawing_s *d)
{
  assert(d);

  if (d->paper) paper_destroy(d->paper);
  if (d->border) border_destroy(d->border);
  if (d->title_block) title_block_destroy(d->title_block);
  if (d->design) design_destroy(d->design);

  free(d);
}

drawing_s *drawing_copy(drawing_s *d)
{
  drawing_s *nd;

  assert(d);

  nd = drawing_create();

  if (d->paper) nd->paper = paper_copy(d->paper);
  if (d->border) nd->border = border_copy(d->border);
  if (d->title_block) nd->title_block = title_block_copy(d->title_block);
  if (d->design) nd->design = design_copy(d->design);

  return nd;
}

void drawing_set(drawing_s *d,
                 paper_s *paper,
                 border_s *border,
                 title_block_s *title_block,
                 design_s *design)
{
  assert(d);
  assert(paper);
  assert(border);
  assert(title_block);
  assert(design);

  drawing_set_paper(d, paper);
  drawing_set_border(d, border);
  drawing_set_title_block(d, title_block);
  drawing_set_design(d, design);
}

void drawing_get(drawing_s *d,
                 paper_s **paper,
                 border_s **border,
                 title_block_s **title_block,
                 design_s **design)
{
  assert(d);
  assert(paper);
  assert(border);
  assert(title_block);
  assert(design);

  *paper = drawing_get_paper(d);
  *border = drawing_get_border(d);
  *title_block = drawing_get_title_block(d);
  *design = drawing_get_design(d);
}


void drawing_set_paper(drawing_s *d, paper_s *p)
{
  assert(d);
  assert(p);
  if (d->paper) paper_destroy(d->paper);
  d->paper = p;
}

paper_s *drawing_get_paper(drawing_s *d)
{
  assert(d);
  return d->paper;
}

void drawing_set_border(drawing_s *d, border_s *b)
{
  assert(d);
  assert(b);
  if (d->border) border_destroy(d->border);
  d->border = b;
}

border_s *drawing_get_border(drawing_s *d)
{
  assert(d);
  return d->border;
}

void drawing_set_title_block(drawing_s *d, title_block_s *tb)
{
  assert(d);
  assert(tb);
  if (d->title_block) title_block_destroy(d->title_block);
  d->title_block = tb;
}

title_block_s *drawing_get_title_block(drawing_s *d)
{
  assert(d);
  return d->title_block;
}

void drawing_set_design(drawing_s *d, design_s *de)
{
  assert(d);
  assert(de);
  if (d->design) design_destroy(d->design);
  d->design = de;
}

design_s *drawing_get_design(drawing_s *d)
{
  assert(d);
  return d->design;
}

