/*!
    @file design-elements.c

    @brief SOURCE_BRIEF

    @timestamp Sun, 27 Dec 2015 07:49:01 +0000

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

    @file design-elements.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-elements.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_elements_s *design_elements_create(void)
{
  design_elements_s *es;

  es = (design_elements_s *)malloc(sizeof(design_elements_s));
  memset(es, 0, sizeof(design_elements_s));

  es->elements = list_create();
  list_set_free(es->elements, design_element_destroy_void);

    // Return RETVAL
  return es;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elements_destroy(design_elements_s *es)
{
    // Sanity check parameters.
  assert(es);

  if (es->elements) list_destroy(es->elements);

  free(es);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_elements_s *design_elements_copy(design_elements_s *es)
{
  design_elements_s *nes;
  design_element_s *e;
  design_element_s *ne;

    // Sanity check parameters.
  assert(es);

  nes = design_elements_create();
  memcpy(nes, es, sizeof(design_elements_s));

  if (es->elements)
  {
    nes->elements = list_create();
    for (e = (design_element_s *)list_head(es->elements);
         e;
         e = (design_element_s *)list_next(es->elements))
    {
      ne = design_element_copy(e);
      list_insert(nes->elements, (void *)ne, (void *)TAIL);
    }
  }

    // Return RETVAL
  return nes;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elements_add_element(design_elements_s *es, design_element_s *e)
{
    // Sanity check parameters.
  assert(es);
  assert(e);
  list_insert(es->elements, e, (void *)TAIL);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_elements_delete_element(design_elements_s *es, int id)
{
  design_element_s *e;

    // Sanity check parameters.
  assert(es);

  if (es->elements)
  {
    for (e = (design_element_s *)list_head(es->elements);
         e;
         e = (design_element_s *)list_next(es->elements))
    {
      if (e->id == id)
      {
        list_delete(es->elements, e);
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

design_element_s *design_elements_get_element_by_id(design_elements_s *es, int id)
{
  design_element_s *e;

    // Sanity check parameters.
  assert(es);

  for (e = (design_element_s *)list_head(es->elements);
       e;
       e = (design_element_s *)list_next(es->elements))
  {
    if (e->id == id)
        // Return RETVAL
  return e;
  }

    // Return RETVAL
  return NULL;
}

