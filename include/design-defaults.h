/*!
    @file design-defaults.h

    @brief Header for design defaults structure definition

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

    @file design-defaults.h

    @brief Header for design defaults structure definition

    Structure and maintenance functions for various defaults for design and
    layers.

  */

#ifndef DESIGN_DEFAULTS_H
#define DESIGN_DEFAULTS_H

  // External include files

#include "color.h"

  // Project specific include files

#include "units.h"

  /*!
    @brief Design defaults structure
  */

typedef struct
{
    /*! @brief Unit type */
  units_t units;
    /*! @brief Width of lines (in units) */
  double line_weight;
    /*! @brief Style of lines */
  char *line_style;
    /*! @brief Style of filled areas */
  char *fill_style;
    /*! @brief Text size for dimension elements */
  double dimension_text_size;
    /*! @brief Precision for dimension elements */
  int dimension_precision;
    /*! @brief Gap between measured angle and extension lines */
  double angular_gap;
    /*! @brief Length of extension lines */
  double angular_extension;
    /*! @brief Gap between end point and extension lines */
  double linear_gap;
    /*! @brief Length of extension line from gap to point farthest from end
               point */
  double linear_extension_above;
    /*! @brief Length of extension line from gap to point nearest to end
               point */
  double linear_extension_below;
    /*! @brief Size of text for tolerance elements */
  double tolerance_text_size;
    /*! @brief "Over" for tolerance elements */
  double tolerance_plus;
    /*! @brief "Under" for tolerance elements */
  double tolerance_minus;
    /*! @brief Precision of tolerance elements */
  int tolerance_precision;
    /*! @brief Background color of various design elements */
  color_s *background_color;
    /*! @brief Color of various drawn design elements */
  color_s *element_color;
} design_defaults_s;

  // Structure maintenance functions

design_defaults_s *design_defaults_create(void);
void design_defaults_destroy_void(void *v);
void design_defaults_destroy(design_defaults_s *d);
design_defaults_s *design_defaults_copy(design_defaults_s *d);

  // Defaults stack functions

void design_defaults_push(design_defaults_s *d);
design_defaults_s *design_defaults_pop(void);
design_defaults_s *design_defaults_current(void);

  // Comprehensive getter/setter

void design_defaults_set(design_defaults_s *d,
                         units_t units,
                         double line_weight,
                         char *line_style,
                         char *fill_style,
                         double dimension_text_size,
                         int dimension_precision,
                         double angular_gap,
                         double angular_extension,
                         double linear_gap,
                         double linear_extension_above,
                         double linear_extension_below,
                         double tolerance_text_size,
                         double tolerance_plus,
                         double tolerance_minus,
                         int tolerance_precision,
                         color_s *background_color,
                         color_s *element_color);
void design_defaults_get(design_defaults_s *d,
                         units_t *units,
                         double *line_weight,
                         char **line_style,
                         char **fill_style,
                         double *dimension_text_size,
                         int *dimension_precision,
                         double *angular_gap,
                         double *angular_extension,
                         double *linear_gap,
                         double *linear_extension_above,
                         double *linear_extension_below,
                         double *tolerance_text_size,
                         double *tolerance_plus,
                         double *tolerance_minus,
                         int *tolerance_precision,
                         color_s **background_color,
                         color_s **element_color);

  // Individual getters/setters/

void design_defaults_set_units(design_defaults_s *d, units_t units);
units_t design_defaults_get_units(design_defaults_s *d);

void design_defaults_set_line_weight(design_defaults_s *d, double line_weight);
double design_defaults_get_line_weight(design_defaults_s *d);

void design_defaults_set_line_style(design_defaults_s *d, char *line_style);
char *design_defaults_get_line_style(design_defaults_s *d);

void design_defaults_set_fill_style(design_defaults_s *d, char *fill_style);
char *design_defaults_get_fill_style(design_defaults_s *d);

void design_defaults_set_dimension_text_size(design_defaults_s *d, double size);
double design_defaults_get_dimension_text_size(design_defaults_s *d);

void design_defaults_set_dimension_precision(design_defaults_s *d, int precision);
int design_defaults_get_dimension_precision(design_defaults_s *d);

void design_defaults_set_angular_gap(design_defaults_s *d, double gap);
double design_defaults_get_angular_gap(design_defaults_s *d);

void design_defaults_set_angular_extension(design_defaults_s *d,
                                           double extension);
double design_defaults_get_angular_extension(design_defaults_s *d);

void design_defaults_set_linear_gap(design_defaults_s *d, double gap);
double design_defaults_get_linear_gap(design_defaults_s *d);

void design_defaults_set_linear_extension_above(design_defaults_s *d,
                                                double extension);
double design_defaults_get_linear_extension_above(design_defaults_s *d);

void design_defaults_set_linear_extension_below(design_defaults_s *d,
                                                double extension);
double design_defaults_get_linear_extension_below(design_defaults_s *d);

void design_defaults_set_tolerance_text_size(design_defaults_s *d, double size);
double design_defaults_get_tolerance_text_size(design_defaults_s *d);

void design_defaults_set_tolerance_plus(design_defaults_s *d, double plus);
double design_defaults_get_tolerance_plus(design_defaults_s *d);

void design_defaults_set_tolerance_minus(design_defaults_s *d, double minus);
double design_defaults_get_tolerance_minus(design_defaults_s *d);

void design_defaults_set_tolerance_precision(design_defaults_s *d, int precision);
int design_defaults_get_tolerance_precision(design_defaults_s *d);

void design_defaults_set_background_color(design_defaults_s *d, color_s *color);
color_s *design_defaults_get_background_color(design_defaults_s *d);

void design_defaults_set_element_color(design_defaults_s *d, color_s *color);
color_s *design_defaults_get_element_color(design_defaults_s *d);

#endif // DESIGN_DEFAULTS_H
