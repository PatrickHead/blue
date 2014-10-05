#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "design-line-styles.h"

static void generate_stock_line_styles(void);
static design_line_styles_s *_create(void);

static design_line_styles_s *_g_stock_line_styles = NULL;

design_line_styles_s *design_line_styles_create(void)
{
  design_line_styles_s *ls;

  generate_stock_line_styles();

  ls = design_line_styles_copy(_g_stock_line_styles);

  return ls;
}

design_line_styles_s *_create(void)
{
  design_line_styles_s *ls;

  ls = (design_line_styles_s *)malloc(sizeof(design_line_styles_s));
  memset(ls, 0, sizeof(design_line_styles_s));

  ls->line_styles = list_new();
  list_set_free(ls->line_styles, design_line_style_destroy_void);

  return ls;
}

void design_line_styles_destroy(design_line_styles_s *lss)
{
  assert(lss);

  if (lss->line_styles) list_destroy(lss->line_styles);

  free(lss);
}

design_line_styles_s *design_line_styles_copy(design_line_styles_s *lss)
{
  design_line_styles_s *nlss;
  design_line_style_s *ls;
  design_line_style_s *nls;

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

  return nlss;
}

void design_line_styles_add_line_style(design_line_styles_s *lss,
                                       design_line_style_s *ls)
{
  assert(lss);
  assert(ls);
  list_insert(lss->line_styles, ls, (void *)TAIL);
}

void design_line_styles_delete_line_style(design_line_styles_s *lss, char *name)
{
  design_line_style_s *ls;

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

design_line_style_s *design_line_styles_get_line_style(design_line_styles_s *lss,
                                                       char *name)
{
  design_line_style_s *ls;

  assert(lss);
  assert(name);

  for (ls = (design_line_style_s *)list_head(lss->line_styles);
       ls;
       ls = (design_line_style_s *)list_next(lss->line_styles))
  {
    if (!strcmp(ls->name, name))
      return ls;
  }

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

