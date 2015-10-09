/*!
    @file design-layers.h

    @brief HEADER_BRIEF

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

    @file design-layers.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_LAYERS_H
#define DESIGN_LAYERS_H

#include "list.h"
#include "design-layer.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  list_s *layers;
} design_layers_s;

design_layers_s *design_layers_create(void);
void design_layers_destroy(design_layers_s *ls);
design_layers_s *design_layers_copy(design_layers_s *ls);
void design_layers_add_layer(design_layers_s *ls, design_layer_s *l);
void design_layers_delete_layer(design_layers_s *ls, int id);
design_layer_s *design_layers_get_layer_by_id(design_layers_s *ls, int id);
design_layer_s *design_layers_get_layer_by_name(design_layers_s *ls, char *name);

#endif // DESIGN_LAYERS_H
