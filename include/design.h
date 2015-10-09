/*!
    @file design.h

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

    @file design.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_H
#define DESIGN_H

#include "design-defaults.h"
#include "design-line-styles.h"
#include "design-fill-styles.h"
#include "design-layers.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  design_defaults_s *defaults;
    /*! @brief ELEMENT_BRIEF */
  design_line_styles_s *line_styles;
    /*! @brief ELEMENT_BRIEF */
  design_fill_styles_s *fill_styles;
    /*! @brief ELEMENT_BRIEF */
  design_layers_s *layers;
  double scaling_factor;
} design_s;

design_s *design_create(void);
void design_destroy(design_s *d);
design_s *design_copy(design_s *d);

void design_set(design_s *d,
                design_defaults_s *defaults,
                design_line_styles_s *line_styles,
                design_fill_styles_s *fill_styles,
                design_layers_s *layers,
                double scaling_factor);
void design_get(design_s *d,
                design_defaults_s **defaults,
                design_line_styles_s **line_styles,
                design_fill_styles_s **fill_styles,
                design_layers_s **layers,
                double *scaling_factor);

void design_set_defaults(design_s *d, design_defaults_s *dflts);
design_defaults_s *design_get_defaults(design_s *d);

void design_set_line_styles(design_s *d, design_line_styles_s *lss);
design_line_styles_s *design_get_line_styles(design_s *d);

void design_set_fill_styles(design_s *d, design_fill_styles_s *lss);
design_fill_styles_s *design_get_fill_styles(design_s *d);

void design_set_layers(design_s *d, design_layers_s *ls);
design_layers_s *design_get_layers(design_s *d);

void design_set_scaling_factor(design_s *d, double sf);
double design_get_scaling_factor(design_s *d);

#endif // DESIGN_H

