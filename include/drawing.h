/*!
    @file drawing.h

    @brief HEADER_BRIEF

    @timestamp Fri, 09 Oct 2015 03:31:15 +0000

    @author Patrick Head  mailto:patrickhead@gmail.com

    @copyright Copyright (C) 2014  Patrick Head

    @license
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.@n
    @n
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.@n
    @n
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

  /*!

    @file drawing.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DRAWING_H
#define DRAWING_H

#include "paper.h"
#include "border.h"
#include "title-block.h"
#include "design.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  paper_s *paper;
    /*! @brief ELEMENT_BRIEF */
  border_s *border;
    /*! @brief ELEMENT_BRIEF */
  title_block_s *title_block;
    /*! @brief ELEMENT_BRIEF */
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
