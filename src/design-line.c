/*!
    @file design-line.c

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

    @file design-line.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "reference.h"

#include "design-line.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_s *design_line_create(void)
{
  design_line_s *line;

  line = (design_line_s *)malloc(sizeof(design_line_s));
  memset(line, 0, sizeof(design_line_s));

  line->start = vertex_create();
  if (line->start) vertex_set(line->start, "start", 0.0, 0.0, 0.0);

  line->end = vertex_create();
  if (line->end) vertex_set(line->end, "end", 0.0, 0.0, 0.0);

    // Return RETVAL
  return line;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_destroy(design_line_s *l)
{
    // Sanity check parameters.
  assert(l);
  if (l->start) vertex_destroy(l->start);
  if (l->end) vertex_destroy(l->end);
  free(l);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_s *design_line_copy(design_line_s *l)
{
  design_line_s *nl;

    // Sanity check parameters.
  assert(l);

  nl = design_line_create();
  memcpy(nl, l, sizeof(design_line_s));

  if (l->start) nl->start = vertex_copy(l->start);
  if (l->end) nl->end = vertex_copy(l->end);

    // Return RETVAL
  return nl;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_set(design_line_s *l,
                     vertex_s *start,
                     vertex_s *end)
{
    // Sanity check parameters.
  assert(l);
  assert(start);
  assert(end);

  design_line_set_start(l, start);
  design_line_set_end(l, end);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_get(design_line_s *l,
                     vertex_s **start,
                     vertex_s **end)
{
    // Sanity check parameters.
  assert(l);
  assert(start);
  assert(end);

  *start = design_line_get_start(l);
  *end = design_line_get_end(l);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_set_start(design_line_s *l, vertex_s *start)
{
    // Sanity check parameters.
  assert(l);
  assert(start);
  if (l->start) vertex_destroy(l->start);
  l->start = start;
  vertex_set_tag(l->start, "start");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_line_get_start(design_line_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->start;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_line_set_end(design_line_s *l, vertex_s *end)
{
    // Sanity check parameters.
  assert(l);
  assert(end);
  if (l->end) vertex_destroy(l->end);
  l->end = end;
  vertex_set_tag(l->end, "end");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_line_get_end(design_line_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->end;
}

