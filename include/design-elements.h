/*!
    @file design-elements.h

    @brief HEADER_BRIEF

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

    @file design-elements.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_ELEMENTS_H
#define DESIGN_ELEMENTS_H

#include "list.h"
#include "design-element.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! brief ELEMENT_BRIEF */
  list_s *elements;
} design_elements_s;

design_elements_s *design_elements_create(void);
void design_elements_destroy(design_elements_s *es);
design_elements_s *design_elements_copy(design_elements_s *es);
void design_elements_add_element(design_elements_s *es, design_element_s *e);
void design_elements_delete_element(design_elements_s *es, int id);
design_element_s *design_elements_get_element_by_id(design_elements_s *ls,
                                                    int id);

#endif // DESIGN_ELEMENTS_H
