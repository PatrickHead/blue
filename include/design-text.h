/*!
    @file design-text.h

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

    @file design-text.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_TEXT_H
#define DESIGN_TEXT_H

#include "vertex.h"

#include "design-text-type.h"
#include "design-anchor-location-type.h"

  /*!
    brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! brief ELEMENT_BRIEF */
  design_text_t type;
    /*! brief ELEMENT_BRIEF */
  vertex_s *location;
    /*! brief ELEMENT_BRIEF */
  double rotation;
    /*! brief ELEMENT_BRIEF */
  design_anchor_location_t anchor_point;
    /*! brief ELEMENT_BRIEF */
  double size;
    /*! brief ELEMENT_BRIEF */
  char *text;
} design_text_s;

design_text_s *design_text_create(void);
void design_text_destroy(design_text_s *t);
design_text_s *design_text_copy(design_text_s *t);

void design_text_set(design_text_s *t,
                     design_text_t type,
                     vertex_s *location,
                     double rotation,
                     design_anchor_location_t anchor_point,
                     double size,
                     char *text);
void design_text_get(design_text_s *t,
                     design_text_t *type,
                     vertex_s **location,
                     double *rotation,
                     design_anchor_location_t *anchor_point,
                     double *size,
                     char **text);

void design_text_set_type(design_text_s *t, design_text_t type); 
design_text_t design_text_get_type(design_text_s *t);
void design_text_set_location(design_text_s *t, vertex_s *location); 
vertex_s *design_text_get_location(design_text_s *t);
void design_text_set_rotation(design_text_s *t, double rotation); 
double design_text_get_rotation(design_text_s *t);
void design_text_set_anchor_point(design_text_s *t,
                                  design_anchor_location_t anchor_point); 
design_anchor_location_t design_text_get_anchor_point(design_text_s *t);
void design_text_set_size(design_text_s *t, double size); 
double design_text_get_size(design_text_s *t);
void design_text_set_text(design_text_s *t, char *text); 
char *design_text_get_text(design_text_s *t);

#endif // DESIGN_TEXT_H
