/*!
    @file drawing.c

    @brief SOURCE_BRIEF

    @timestamp Fri, 09 Oct 2015 05:38:21 +0000

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

    @file drawing.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "drawing.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

drawing_s *drawing_create(void)
{
  drawing_s *d;
  d = (drawing_s *)malloc(sizeof(drawing_s));
  memset(d, 0, sizeof(drawing_s));
    // Return RETVAL
  return d;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void drawing_destroy(drawing_s *d)
{
    // Sanity check parameters.
  assert(d);

  if (d->paper) paper_destroy(d->paper);
  if (d->border) border_destroy(d->border);
  if (d->title_block) title_block_destroy(d->title_block);
  if (d->design) design_destroy(d->design);

  free(d);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

drawing_s *drawing_copy(drawing_s *d)
{
  drawing_s *nd;

    // Sanity check parameters.
  assert(d);

  nd = drawing_create();

  if (d->paper) nd->paper = paper_copy(d->paper);
  if (d->border) nd->border = border_copy(d->border);
  if (d->title_block) nd->title_block = title_block_copy(d->title_block);
  if (d->design) nd->design = design_copy(d->design);

    // Return RETVAL
  return nd;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void drawing_set(drawing_s *d,
                 paper_s *paper,
                 border_s *border,
                 title_block_s *title_block,
                 design_s *design)
{
    // Sanity check parameters.
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

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void drawing_get(drawing_s *d,
                 paper_s **paper,
                 border_s **border,
                 title_block_s **title_block,
                 design_s **design)
{
    // Sanity check parameters.
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


  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void drawing_set_paper(drawing_s *d, paper_s *p)
{
    // Sanity check parameters.
  assert(d);
  assert(p);
  if (d->paper) paper_destroy(d->paper);
  d->paper = p;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

paper_s *drawing_get_paper(drawing_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->paper;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void drawing_set_border(drawing_s *d, border_s *b)
{
    // Sanity check parameters.
  assert(d);
  assert(b);
  if (d->border) border_destroy(d->border);
  d->border = b;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

border_s *drawing_get_border(drawing_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->border;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void drawing_set_title_block(drawing_s *d, title_block_s *tb)
{
    // Sanity check parameters.
  assert(d);
  assert(tb);
  if (d->title_block) title_block_destroy(d->title_block);
  d->title_block = tb;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

title_block_s *drawing_get_title_block(drawing_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->title_block;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void drawing_set_design(drawing_s *d, design_s *de)
{
    // Sanity check parameters.
  assert(d);
  assert(de);
  if (d->design) design_destroy(d->design);
  d->design = de;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_s *drawing_get_design(drawing_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->design;
}

