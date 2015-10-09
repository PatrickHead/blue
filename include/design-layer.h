/*!
    @file design-layer.h

    @brief HEADER_BRIEF

    @timestamp Tue, 11 Nov 2014 07:22:32 +0000

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

    @file design-layer.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_LAYER_H
#define DESIGN_LAYER_H

#include "design-defaults.h"
#include "design-visibility-type.h"
#include "design-elements.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  int id;
    /*! @brief ELEMENT_BRIEF */
  char *name;
    /*! @brief ELEMENT_BRIEF */
  design_visibility_t visibility;
    /*! @brief ELEMENT_BRIEF */
  design_defaults_s *defaults;
    /*! @brief ELEMENT_BRIEF */
  design_elements_s *elements;
} design_layer_s;

design_layer_s *design_layer_create(void);
void design_layer_destroy_void(void *l);
void design_layer_destroy(design_layer_s *l);
design_layer_s *design_layer_copy(design_layer_s *l);

void design_layer_set(design_layer_s *l,
                      int id,
                      char *name,
                      design_visibility_t visibility,
                      design_defaults_s *defaults,
                      design_elements_s *elements);
void design_layer_get(design_layer_s *l,
                      int *id,
                      char **name,
                      design_visibility_t *visibility,
                      design_defaults_s **defaults,
                      design_elements_s **elements);

void design_layer_set_id(design_layer_s *l, int id);
int design_layer_get_id(design_layer_s *l);

void design_layer_set_name(design_layer_s *l, char *name);
char *design_layer_get_name(design_layer_s *l);

void design_layer_set_visibility(design_layer_s *l,
                                 design_visibility_t visibility);
design_visibility_t design_layer_get_visibility(design_layer_s *l);

void design_layer_set_defaults(design_layer_s *l, design_defaults_s *d);
design_defaults_s *design_layer_get_defaults(design_layer_s *l);

void design_layer_set_elements(design_layer_s *l, design_elements_s *es);
design_elements_s *design_layer_get_elements(design_layer_s *l);

#endif // DESIGN_LAYER_H
