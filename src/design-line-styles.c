/*!
    @file design-line-styles.c

    @brief SOURCE_BRIEF

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

    @file design-line-styles.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-line-styles.h"

static void generate_stock_line_styles(void);
static design_line_styles_s *_create(void);

static design_line_styles_s *_g_stock_line_styles = NULL;

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_styles_s *design_line_styles_create(void)
{
  design_line_styles_s *ls;

  generate_stock_line_styles();

  ls = design_line_styles_copy(_g_stock_line_styles);

    // Return RETVAL
  return ls;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_styles_s *_create(void)
{
  design_line_styles_s *ls;

  ls = (design_line_styles_s *)malloc(sizeof(design_line_styles_s));
  memset(ls, 0, sizeof(design_line_styles_s));

  ls->line_styles = list_create();
  list_set_free(ls->line_styles, design_line_style_destroy_void);

    // Return RETVAL
  return ls;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_styles_destroy(design_line_styles_s *lss)
{
    // Sanity check parameters.
  assert(lss);

  if (lss->line_styles) list_destroy(lss->line_styles);

  free(lss);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_styles_s *design_line_styles_copy(design_line_styles_s *lss)
{
  design_line_styles_s *nlss;
  design_line_style_s *ls;
  design_line_style_s *nls;

    // Sanity check parameters.
  assert(lss);

  nlss = _create();

  if (lss->line_styles)
  {
    for (ls = (design_line_style_s *)list_head(lss->line_styles);
         ls;
         ls = (design_line_style_s *)list_next(lss->line_styles))
    {
      nls = design_line_style_copy(ls);
      list_insert(nlss->line_styles, (void *)nls, (void *)TAIL);
    }
  }

    // Return RETVAL
  return nlss;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_styles_add_line_style(design_line_styles_s *lss,
                                       design_line_style_s *ls)
{
    // Sanity check parameters.
  assert(lss);
  assert(ls);
  list_insert(lss->line_styles, ls, (void *)TAIL);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_styles_delete_line_style(design_line_styles_s *lss, char *name)
{
  design_line_style_s *ls;

    // Sanity check parameters.
  assert(lss);
  assert(name);

  if (lss->line_styles)
  {
    for (ls = (design_line_style_s *)list_head(lss->line_styles);
         ls;
         ls = (design_line_style_s *)list_next(lss->line_styles))
    {
      if (!strcmp(ls->name, name))
      {
        list_delete(lss->line_styles, ls);
        break;
      }
    }
  }
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_s *design_line_styles_get_line_style(design_line_styles_s *lss,
                                                       char *name)
{
  design_line_style_s *ls;

    // Sanity check parameters.
  assert(lss);
  assert(name);

  for (ls = (design_line_style_s *)list_head(lss->line_styles);
       ls;
       ls = (design_line_style_s *)list_next(lss->line_styles))
  {
    if (!strcmp(ls->name, name))
        // Return RETVAL
  return ls;
  }

    // Return RETVAL
  return NULL;
}

static void generate_stock_line_styles(void)
{
  design_line_style_s *ls;
  design_line_style_segment_s *lss;

  if (_g_stock_line_styles) return;

  _g_stock_line_styles = _create();

  ls = design_line_style_create();
  design_line_style_set_name(ls, "dotted");
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.05);
  design_line_style_add_segment(ls, lss);
  design_line_styles_add_line_style(_g_stock_line_styles, ls);

  ls = design_line_style_create();
  design_line_style_set_name(ls, "dashed");
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.5);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.5);
  design_line_style_add_segment(ls, lss);
  design_line_styles_add_line_style(_g_stock_line_styles, ls);

  ls = design_line_style_create();
  design_line_style_set_name(ls, "dotdash");
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.0);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.25);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.5);
  design_line_style_add_segment(ls, lss);
  lss = design_line_style_segment_create();
  design_line_style_segment_set(lss, 0.25);
  design_line_style_add_segment(ls, lss);
  design_line_styles_add_line_style(_g_stock_line_styles, ls);
}

