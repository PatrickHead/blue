#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "design-fill-styles.h"

design_fill_styles_s *design_fill_styles_create(void)
{
  design_fill_styles_s *fs;

  fs = (design_fill_styles_s *)malloc(sizeof(design_fill_styles_s));
  memset(fs, 0, sizeof(design_fill_styles_s));

  fs->fill_styles = list_new();
  list_set_free(fs->fill_styles, design_fill_style_destroy_void);

  return fs;
}

void design_fill_styles_destroy(design_fill_styles_s *fss)
{
  assert(fss);

  if (fss->fill_styles) list_destroy(fss->fill_styles);

  free(fss);
}

design_fill_styles_s *design_fill_styles_copy(design_fill_styles_s *fss)
{
  design_fill_styles_s *nfss;
  design_fill_style_s *fs;
  design_fill_style_s *nfs;

  assert(fss);

  nfss = design_fill_styles_create();

  if (fss->fill_styles)
  {
    for (fs = (design_fill_style_s *)list_head(fss->fill_styles);
         fs;
         fs = (design_fill_style_s *)list_next(fss->fill_styles))
    {
      nfs = design_fill_style_copy(fs);
      list_insert(nfss->fill_styles, (void *)nfs, (void *)TAIL);
    }
  }

  return nfss;
}

void design_fill_styles_add_fill_style(design_fill_styles_s *fss,
                                       design_fill_style_s *fs)
{
  assert(fss);
  assert(fs);
  list_insert(fss->fill_styles, fs, (void *)TAIL);
}

void design_fill_styles_delete_fill_style(design_fill_styles_s *fss, char *name)
{
  design_fill_style_s *fs;

  assert(fss);
  assert(name);

  if (fss->fill_styles)
  {
    for (fs = (design_fill_style_s *)list_head(fss->fill_styles);
         fs;
         fs = (design_fill_style_s *)list_next(fss->fill_styles))
    {
      if (!strcmp(fs->name, name))
      {
        list_delete(fss->fill_styles, fs);
        break;
      }
    }
  }
}

design_fill_style_s *design_fill_styles_get_fill_style(design_fill_styles_s *fss,
                                                       char *name)
{
  design_fill_style_s *fs;

  assert(fss);
  assert(name);

  for (fs = (design_fill_style_s *)list_head(fss->fill_styles);
       fs;
       fs = (design_fill_style_s *)list_next(fss->fill_styles))
  {
    if (!strcmp(fs->name, name))
      return fs;
  }

  return NULL;
}

