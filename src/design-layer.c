/*!
    @file design-layer.c

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

    @file design-layer.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "list.h"
#include "reference.h"

#include "blue.h"

#include "design-elements.h"
#include "design-layer.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_layer_s *design_layer_create(void)
{
  design_layer_s *layer;

  layer = (design_layer_s *)malloc(sizeof(design_layer_s));
  memset(layer, 0, sizeof(design_layer_s));

  layer->id = reference_new(BLUE_REFERENCE);
  layer->defaults = design_defaults_create();
  layer->elements = design_elements_create();

    // Return RETVAL
  return layer;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layer_destroy_void(void *l)
{
  design_layer_destroy((design_layer_s *)l);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layer_destroy(design_layer_s *l)
{
    // Sanity check parameters.
  assert(l);

  if (l->name) free(l->name);
  if (l->elements) design_elements_destroy(l->elements);
  if (l->defaults) design_defaults_destroy(l->defaults);
  free(l);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_layer_s *design_layer_copy(design_layer_s *l)
{
  design_layer_s *nl;

    // Sanity check parameters.
  assert(l);

  nl = design_layer_create();
  memcpy(nl, l, sizeof(design_layer_s));

  if (l->elements)
    nl->elements = design_elements_copy(l->elements);

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

void design_layer_set(design_layer_s *l,
                      int id,
                      char *name,
                      design_visibility_t visibility,
                      design_defaults_s *defaults,
                      design_elements_s *elements)
{
    // Sanity check parameters.
  assert(l);
  assert(name);
  assert(defaults);
  assert(elements);

  design_layer_set_id(l, id);
  design_layer_set_name(l, name);
  design_layer_set_visibility(l, visibility);
  design_layer_set_defaults(l, defaults);
  design_layer_set_elements(l, elements);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layer_get(design_layer_s *l,
                      int *id,
                      char **name,
                      design_visibility_t *visibility,
                      design_defaults_s **defaults,
                      design_elements_s **elements)
{
    // Sanity check parameters.
  assert(l);
  assert(id);
  assert(name);
  assert(visibility);
  assert(defaults);
  assert(elements);

  *id = design_layer_get_id(l);
  *name = design_layer_get_name(l);
  *visibility = design_layer_get_visibility(l);
  *defaults = design_layer_get_defaults(l);
  *elements = design_layer_get_elements(l);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layer_set_id(design_layer_s *l, int id)
{
    // Sanity check parameters.
  assert(l);
  l->id = id;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int design_layer_get_id(design_layer_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->id;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layer_set_name(design_layer_s *l, char *name)
{
    // Sanity check parameters.
  assert(l);
  assert(name);

  if (l->name) free(l->name);
  l->name = strdup(name);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

char *design_layer_get_name(design_layer_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->name;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layer_set_visibility(design_layer_s *l,
                                 design_visibility_t visibility)
{
    // Sanity check parameters.
  assert(l);

  l->visibility = visibility;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_visibility_t design_layer_get_visibility(design_layer_s *l)
{
    // Sanity check parameters.
  assert(l);

    // Return RETVAL
  return l->visibility;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layer_set_elements(design_layer_s *l, design_elements_s *es)
{
    // Sanity check parameters.
  assert(l);
  assert(es);

  if (l->elements) design_elements_destroy(l->elements);
  l->elements = design_elements_copy(es);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_elements_s *design_layer_get_elements(design_layer_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->elements;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layer_set_defaults(design_layer_s *l, design_defaults_s *d)
{
    // Sanity check parameters.
  assert(l);
  assert(d);

  if (l->defaults) design_defaults_destroy(l->defaults);
  l->defaults = design_defaults_copy(d);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_defaults_s *design_layer_get_defaults(design_layer_s *l)
{
    // Sanity check parameters.
  assert(l);
    // Return RETVAL
  return l->defaults;
}

