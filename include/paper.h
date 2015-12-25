/*!
    @file paper.h

    @brief HEADER_BRIEF

    @timestamp Fri, 09 Oct 2015 05:38:21 +0000

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

    @file paper.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef PAPER_H
#define PAPER_H

#include "units.h"
#include "margins.h"
#include "color.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef enum
{
  paper_size_type_iso_a0,
  paper_size_type_iso_a1,
  paper_size_type_iso_a2,
  paper_size_type_iso_a3,
  paper_size_type_iso_a4,
  paper_size_type_ansi_a,
  paper_size_type_ansi_b,
  paper_size_type_ansi_c,
  paper_size_type_ansi_d,
  paper_size_type_ansi_e,
  paper_size_type_arch_a,
  paper_size_type_arch_b,
  paper_size_type_arch_c,
  paper_size_type_arch_d,
  paper_size_type_arch_e,
  paper_size_type_arch_e1,
  paper_size_type_arch_e2,
  paper_size_type_arch_e3,
  paper_size_type_letter,
  paper_size_type_legal,
  paper_size_type_tabloid,
  paper_size_type_user_defined
} paper_size_t;

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef enum
{
  paper_orientation_type_portrait,
  paper_orientation_type_landscape
} paper_orientation_t;

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  units_t units;
    /*! @brief ELEMENT_BRIEF */
  paper_size_t size;
    /*! @brief ELEMENT_BRIEF */
  paper_orientation_t orientation;
    /*! @brief ELEMENT_BRIEF */
  margins_s *margins;
    /*! @brief ELEMENT_BRIEF */
  double width;
    /*! @brief ELEMENT_BRIEF */
  double height;
    /*! @brief ELEMENT_BRIEF */
  color_s *color;
} paper_s;

paper_s *paper_create(void);
void paper_destroy(paper_s *p);
paper_s *paper_copy(paper_s *p);

void paper_set(paper_s *p,
               units_t units,
               paper_size_t size,
               paper_orientation_t orientation,
               margins_s *margins,
               double width,
               double height,
               color_s *color);
void paper_get(paper_s *p,
               units_t *units,
               paper_size_t *size,
               paper_orientation_t *orientation,
               margins_s **margins,
               double *width,
               double *height,
               color_s **color);

void paper_set_units(paper_s *p, units_t ut);
units_t paper_get_units(paper_s *p);

void paper_set_size(paper_s *p, paper_size_t st);
paper_size_t paper_get_size(paper_s *p);

void paper_set_orientation(paper_s *p, paper_orientation_t o);
paper_orientation_t paper_get_orientation(paper_s *p);

void paper_set_margins(paper_s *p, margins_s *m);
margins_s *paper_get_margins(paper_s *p);

void paper_set_width(paper_s *p, double width);
double paper_get_width(paper_s *p);

void paper_set_height(paper_s *p, double height);
double paper_get_height(paper_s *p);

void paper_set_color(paper_s *p, color_s *color);
color_s *paper_get_color(paper_s *p);

char* paper_size2str(paper_size_t type);
paper_size_t str2paper_size(char* s);

char* paper_orientation2str(paper_orientation_t type);
paper_orientation_t str2paper_orientation(char* s);

#endif // PAPER_H
