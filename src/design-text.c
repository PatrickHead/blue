/*!
    @file design-text.c

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

    @file design-text.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "reference.h"

#include "design-text.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_text_s *design_text_create(void)
{
  design_text_s *text;

  text = (design_text_s *)malloc(sizeof(design_text_s));
  memset(text, 0, sizeof(design_text_s));

  text->location = vertex_create();
  if (text->location) vertex_set(text->location, "location", 0.0, 0.0, 0.0);

    // Return RETVAL
  return text;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_destroy(design_text_s *t)
{
    // Sanity check parameters.
  assert(t);
  if (t->location) vertex_destroy(t->location);
  if (t->text) free(t->text);
  free(t);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_text_s *design_text_copy(design_text_s *t)
{
  design_text_s *nt;

    // Sanity check parameters.
  assert(t);

  nt = design_text_create();
  memcpy(nt, t, sizeof(design_text_s));
  if (t->text) nt->location = vertex_copy(t->location);
  if (t->text) nt->text = strdup(t->text);

    // Return RETVAL
  return nt;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_set_type(design_text_s *t, design_text_t type)
{
    // Sanity check parameters.
  assert(t);
  t->type = type;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_text_t design_text_get_type(design_text_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->type;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_set(design_text_s *t,
                     design_text_t type,
                     vertex_s *location,
                     double rotation,
                     design_anchor_location_t anchor_point,
                     double size,
                     char *text)
{
    // Sanity check parameters.
  assert(t);
  assert(location);
  assert(text);

  design_text_set_type(t, type);
  design_text_set_location(t, location);
  design_text_set_rotation(t, rotation);
  design_text_set_anchor_point(t, anchor_point);
  design_text_set_size(t, size);
  design_text_set_text(t, text);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_get(design_text_s *t,
                     design_text_t *type,
                     vertex_s **location,
                     double *rotation,
                     design_anchor_location_t *anchor_point,
                     double *size,
                     char **text)
{
    // Sanity check parameters.
  assert(t);
  assert(type);
  assert(location);
  assert(rotation);
  assert(anchor_point);
  assert(size);
  assert(text);

  *type = design_text_get_type(t);
  *location = design_text_get_location(t);
  *rotation = design_text_get_rotation(t);
  *anchor_point = design_text_get_anchor_point(t);
  *size = design_text_get_size(t);
  *text = design_text_get_text(t);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_set_location(design_text_s *t, vertex_s *location)
{
    // Sanity check parameters.
  assert(t);
  assert(location);
  if (t->location) vertex_destroy(t->location);
  t->location = location;
  vertex_set_tag(t->location, "location");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *design_text_get_location(design_text_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->location;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_set_rotation(design_text_s *t, double rotation)
{
    // Sanity check parameters.
  assert(t);
  t->rotation = rotation;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_text_get_rotation(design_text_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->rotation;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_set_anchor_point(design_text_s *t, design_anchor_location_t anchor_point)
{
    // Sanity check parameters.
  assert(t);
  t->anchor_point = anchor_point;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_anchor_location_t design_text_get_anchor_point(design_text_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->anchor_point;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_set_size(design_text_s *t, double size)
{
    // Sanity check parameters.
  assert(t);
  t->size = size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_text_get_size(design_text_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_text_set_text(design_text_s *t, char * text)
{
    // Sanity check parameters.
  assert(t);
  if (t->text) free(t->text);
  t->text = strdup(text);
}

char * design_text_get_text(design_text_s *t)
{
    // Sanity check parameters.
  assert(t);
    // Return RETVAL
  return t->text;
}

