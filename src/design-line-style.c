/*!
    @file design-line-style.c

    @brief SOURCE_BRIEF

    @timestamp Tue, 11 Nov 2014 07:22:33 +0000

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

    @file design-line-style.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-line-style.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_s *design_line_style_create(void)
{
  design_line_style_s *dls;

  dls = (design_line_style_s *)malloc(sizeof(design_line_style_s));
  memset(dls, 0, sizeof(design_line_style_s));

  dls->name = strdup("AUTO");
  dls->line_style_segments = design_line_style_segments_create();

    // Return RETVAL
  return dls;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_destroy_void(void *v)
{
    // Sanity check parameters.
  assert(v);
  design_line_style_destroy((design_line_style_s *)v);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_destroy(design_line_style_s *dls)
{
    // Sanity check parameters.
  assert(dls);

  if (dls->name) free(dls->name);
  if (dls->line_style_segments)
    design_line_style_segments_destroy(dls->line_style_segments);

  free(dls);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_s *design_line_style_copy(design_line_style_s *dls)
{
  design_line_style_s *ndls;

    // Sanity check parameters.
  assert(dls);

  ndls = design_line_style_create();
  memcpy(ndls, dls, sizeof(design_line_style_s));

  if (dls->name) ndls->name = strdup(dls->name);
  if (dls->line_style_segments)
  {
    ndls->line_style_segments =
      design_line_style_segments_copy(dls->line_style_segments);
  }

    // Return RETVAL
  return ndls;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_set(design_line_style_s *dls,
                           char *name,
                           design_line_style_segments_s *line_style_segments)
{
    // Sanity check parameters.
  assert(dls);
  assert(name);
  assert(line_style_segments);

  design_line_style_set_name(dls, name);
  design_line_style_set_line_style_segments(dls, line_style_segments);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_get(design_line_style_s *dls,
                           char **name,
                           design_line_style_segments_s **line_style_segments)
{
    // Sanity check parameters.
  assert(dls);
  assert(name);
  assert(line_style_segments);

  *name = design_line_style_get_name(dls);
  *line_style_segments = design_line_style_get_line_style_segments(dls);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_set_name(design_line_style_s *dls, char *name)
{
    // Sanity check parameters.
  assert(dls);
  assert(name);

  if (dls->name) free(dls->name);
  dls->name = strdup(name);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

char *design_line_style_get_name(design_line_style_s *dls)
{
    // Sanity check parameters.
  assert(dls);
    // Return RETVAL
  return dls->name;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_set_line_style_segments(design_line_style_s *dls,
                                               design_line_style_segments_s *lsss)
{
    // Sanity check parameters.
  assert(dls);
  assert(lsss);

  if (dls->line_style_segments)
    design_line_style_segments_destroy(dls->line_style_segments);
  dls->line_style_segments = lsss;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_style_segments_s *design_line_style_get_line_style_segments(
  design_line_style_s *dls)
{
    // Sanity check parameters.
  assert(dls);
    // Return RETVAL
  return dls->line_style_segments;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_style_add_segment(design_line_style_s *dls,
                                   design_line_style_segment_s *lss)
{
    // Sanity check parameters.
  assert(dls);
  assert(lss);

  design_line_style_segments_add_line_style_segment(dls->line_style_segments,
                                                    lss);
}

