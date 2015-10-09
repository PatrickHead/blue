/*!
    @file design-element.h

    @brief Header file for base design element data structure definition

    @timestamp Fri, 28 Nov 2014 17:43:51 +0000

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

    @file design-element.h

    @brief Header file for base design element data structure definition

    Structure and maintenance functions for base design element data.

  */

#ifndef DESIGN_ELEMENT_H
#define DESIGN_ELEMENT_H

  // External include files

#include "vertex.h"
#include "color.h"

  // Project specific include files

#include "units.h"
#include "design-dimension.h"
#include "design-elliptic.h"
#include "design-line.h"
#include "design-point.h"
#include "design-polyline.h"
#include "design-spline.h"
#include "design-text.h"
#include "design-tolerance.h"
#include "design-element-type.h"

  /*!
    @brief Design element structure
  */

typedef struct
{
    /*! @brief Unique identifier */
  int id;
    /*! @brief Type of design element */
  design_element_t type;
    /*! @brief Unit of measurement */
  units_t units;
    /*! @brief Width of drawn element parts */
  double line_weight;
    /*! @brief Style of drawn lines */
  char *line_style;
    /*! @brief Style of filled areas of element */
  char *fill_style;
    /*! @brief Color of drawn elements */
  color_s *color;
  union
  {
    /*! @brief dimension element data */
    design_dimension_s *dimension;
    /*! @brief elliptic curve element data */
    design_elliptic_s *elliptic;
    /*! @brief line element data */
    design_line_s *line;
    /*! @brief point element data */
    design_point_s *point;
    /*! @brief polyline (series of connected lines) element data */
    design_polyline_s *polyline;
    /*! @brief spline curve element data */
    design_spline_s *spline;
    /*! @brief descriptive text element data */
    design_text_s *text;
    /*! @brief tolerance annotation element data */
    design_tolerance_s *tolerance;
  };
} design_element_s;

  // Structure maintenance functions

design_element_s *design_element_create(void);
void design_element_destroy_void(void *v);
void design_element_destroy(design_element_s *e);
design_element_s *design_element_copy(design_element_s *e);

  // Comprehensive getter/setter

void design_element_set(design_element_s *e,
                        int id,
                        design_element_t type,
                        units_t units,
                        double line_weight,
                        char *line_style,
                        char *fill_style,
                        color_s *color,
                        void *data);
void design_element_get(design_element_s *e,
                        int *id,
                        design_element_t *type,
                        units_t *units,
                        double *line_weight,
                        char **line_style,
                        char **fill_style,
                        color_s **color,
                        void **data);

  // Individual getters/setters

void design_element_set_id(design_element_s *e, int id); 
int design_element_get_id(design_element_s *e);

void design_element_set_type(design_element_s *e, design_element_t type);
design_element_t design_element_get_type(design_element_s *e);

void design_element_set_units(design_element_s *e, units_t units);
units_t design_element_get_units(design_element_s *e);

void design_element_set_line_weight(design_element_s *e, double lw);
double design_element_get_line_weight(design_element_s *e);

void design_element_set_line_style(design_element_s *e, char *style);
char *design_element_get_line_style(design_element_s *e);

void design_element_set_fill_style(design_element_s *e, char *style);
char *design_element_get_fill_style(design_element_s *e);

void design_element_set_color(design_element_s *e, color_s *color);
color_s *design_element_get_color(design_element_s *e);

void design_element_set_dimension(design_element_s *e, design_dimension_s *d);
design_dimension_s *design_element_get_dimension(design_element_s *e);

void design_element_set_elliptic(design_element_s *e, design_elliptic_s *el);
design_elliptic_s *design_element_get_elliptic(design_element_s *e);

void design_element_set_line(design_element_s *e, design_line_s *l);
design_line_s *design_element_get_line(design_element_s *e);

void design_element_set_point(design_element_s *e, design_point_s *p);
design_point_s *design_element_get_point(design_element_s *e);

void design_element_set_polyline(design_element_s *e, design_polyline_s *pl);
design_polyline_s *design_element_get_polyline(design_element_s *e);

void design_element_set_spline(design_element_s *e, design_spline_s *s);
design_spline_s *design_element_get_spline(design_element_s *e);

void design_element_set_text(design_element_s *e, design_text_s *t);
design_text_s *design_element_get_text(design_element_s *e);

void design_element_set_tolerance(design_element_s *e, design_tolerance_s *t);
design_tolerance_s *design_element_get_tolerance(design_element_s *e);

#endif // DESIGN_ELEMENT_H
