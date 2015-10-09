/*!
    @file design-layers.c

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

    @file design-layers.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-layers.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_layers_s *design_layers_create(void)
{
  design_layers_s *ls;

  ls = (design_layers_s *)malloc(sizeof(design_layers_s));
  memset(ls, 0, sizeof(design_layers_s));

  ls->layers = list_create();
  list_set_free(ls->layers, design_layer_destroy_void);

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

void design_layers_destroy(design_layers_s *ls)
{
    // Sanity check parameters.
  assert(ls);

  if (ls->layers) list_destroy(ls->layers);

  free(ls);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_layers_s *design_layers_copy(design_layers_s *ls)
{
  design_layers_s *nls;
  design_layer_s *l;
  design_layer_s *nl;

    // Sanity check parameters.
  assert(ls);

  nls = design_layers_create();
  memcpy(nls, ls, sizeof(design_layers_s));

  if (ls->layers)
  {
    nls->layers = list_create();
    for (l = (design_layer_s *)list_head(ls->layers);
         l;
         l = (design_layer_s *)list_next(ls->layers))
    {
      nl = design_layer_copy(l);
      list_insert(nls->layers, (void *)nl, (void *)TAIL);
    }
  }

    // Return RETVAL
  return nls;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layers_add_layer(design_layers_s *ls, design_layer_s *l)
{
    // Sanity check parameters.
  assert(ls);
  assert(l);
  list_insert(ls->layers, l, (void *)TAIL);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_layers_delete_layer(design_layers_s *ls, int id)
{
  design_layer_s *l;

    // Sanity check parameters.
  assert(ls);

  if (ls->layers)
  {
    for (l = (design_layer_s *)list_head(ls->layers);
         l;
         l = (design_layer_s *)list_next(ls->layers))
    {
      if (l->id == id)
      {
        list_delete(ls->layers, l);
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

design_layer_s *design_layers_get_layer_by_id(design_layers_s *ls, int id)
{
  design_layer_s *l;

    // Sanity check parameters.
  assert(ls);

  for (l = (design_layer_s *)list_head(ls->layers);
       l;
       l = (design_layer_s *)list_next(ls->layers))
  {
    if (l->id == id)
        // Return RETVAL
  return l;
  }

    // Return RETVAL
  return NULL;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_layer_s *design_layers_get_layer_by_name(design_layers_s *ls, char *name)
{
  design_layer_s *l;

    // Sanity check parameters.
  assert(ls);
  assert(name);

  for (l = (design_layer_s *)list_head(ls->layers);
       l;
       l = (design_layer_s *)list_next(ls->layers))
  {
    if (!strcmp(l->name, name))
        // Return RETVAL
  return l;
  }

    // Return RETVAL
  return NULL;
}

