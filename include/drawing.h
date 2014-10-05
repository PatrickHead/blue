#ifndef DRAWING_H
#define DRAWING_H

#include "paper.h"
#include "border.h"
#include "title-block.h"
#include "design.h"

typedef struct
{
  paper_s *paper;
  border_s *border;
  title_block_s *title_block;
  design_s *design;
} drawing_s;

drawing_s *drawing_create(void);
void drawing_destroy(drawing_s *d);
drawing_s *drawing_copy(drawing_s *d);

void drawing_set(drawing_s *d,
                 paper_s *paper,
                 border_s *border,
                 title_block_s *title_block,
                 design_s *design);
void drawing_get(drawing_s *d,
                 paper_s **paper,
                 border_s **border,
                 title_block_s **title_block,
                 design_s **design);

void drawing_set_paper(drawing_s *d, paper_s *p);
paper_s *drawing_get_paper(drawing_s *d);

void drawing_set_border(drawing_s *d, border_s *b);
border_s *drawing_get_border(drawing_s *d);

void drawing_set_title_block(drawing_s *d, title_block_s *tb);
title_block_s *drawing_get_title_block(drawing_s *d);

void drawing_set_design(drawing_s *d, design_s *de);
design_s *drawing_get_design(drawing_s *d);

#endif // DRAWING_H
