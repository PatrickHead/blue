/*!
    @file design-fill-styles.c

    @brief SOURCE_BRIEF

    @timestamp Mon, 06 Jan 2014 15:17:36 +0000

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

    @file design-fill-styles.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-fill-styles.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_styles_s *design_fill_styles_create(void)
{
  design_fill_styles_s *fs;

  fs = (design_fill_styles_s *)malloc(sizeof(design_fill_styles_s));
  memset(fs, 0, sizeof(design_fill_styles_s));

  fs->fill_styles = list_create();
  list_set_free(fs->fill_styles, design_fill_style_destroy_void);

    // Return RETVAL
  return fs;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_fill_styles_destroy(design_fill_styles_s *fss)
{
    // Sanity check parameters.
  assert(fss);

  if (fss->fill_styles) list_destroy(fss->fill_styles);

  free(fss);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_styles_s *design_fill_styles_copy(design_fill_styles_s *fss)
{
  design_fill_styles_s *nfss;
  design_fill_style_s *fs;
  design_fill_style_s *nfs;

    // Sanity check parameters.
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

    // Return RETVAL
  return nfss;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_fill_styles_add_fill_style(design_fill_styles_s *fss,
                                       design_fill_style_s *fs)
{
    // Sanity check parameters.
  assert(fss);
  assert(fs);
  list_insert(fss->fill_styles, fs, (void *)TAIL);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_fill_styles_delete_fill_style(design_fill_styles_s *fss, char *name)
{
  design_fill_style_s *fs;

    // Sanity check parameters.
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

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_style_s *design_fill_styles_get_fill_style(design_fill_styles_s *fss,
                                                       char *name)
{
  design_fill_style_s *fs;

    // Sanity check parameters.
  assert(fss);
  assert(name);

  for (fs = (design_fill_style_s *)list_head(fss->fill_styles);
       fs;
       fs = (design_fill_style_s *)list_next(fss->fill_styles))
  {
    if (!strcmp(fs->name, name))
        // Return RETVAL
  return fs;
  }

    // Return RETVAL
  return NULL;
}

