/*!
    @file design-defaults.c

    @brief SOURCE_BRIEF

    @timestamp Sat, 27 Dec 2014 11:33:10 +0000

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

    @file design-defaults.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "list.h"

#include "design-defaults.h"

static list_s *_g_list = NULL;

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_init(void)
{
  if (!_g_list)
  {
    _g_list = list_create();
    if (!_g_list) return;
    list_set_free(_g_list, design_defaults_destroy_void);
  }

  list_push(_g_list, (void *)design_defaults_create());
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_cleanup(void)
{
  if (_g_list) list_destroy(_g_list);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_defaults_s *design_defaults_create(void)
{
  design_defaults_s *d;

  d = (design_defaults_s *)malloc(sizeof(design_defaults_s));
  memset(d, 0, sizeof(design_defaults_s));

  d->units = units_type_mm;
  d->line_weight = 1.0;
  d->line_style = strdup("solid");
  d->fill_style = strdup("NONE");
  d->dimension_text_size = 4.0;
  d->dimension_precision = 2;
  d->angular_gap = 5.0;
  d->angular_extension = 25.0;
  d->linear_gap = 6.0;
  d->linear_extension_above = 12.0;
  d->linear_extension_below = 6.0;
  d->tolerance_text_size = 4.0;
  d->tolerance_plus = 0.0;
  d->tolerance_minus = 0.0;
  d->tolerance_precision = 2;

  d->background_color = color_create();
  color_set_tag(d->background_color, "background-color");
  color_white(d->background_color);

  d->element_color = color_create();
  color_set_tag(d->element_color, "element-color");
  color_black(d->element_color);

    // Return RETVAL
  return d;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_destroy_void(void *v)
{
  design_defaults_destroy((design_defaults_s *)v);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_destroy(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);

  if (d->line_style) free(d->line_style);
  if (d->fill_style) free(d->fill_style);
  if (d->background_color) color_destroy(d->background_color);
  if (d->element_color) color_destroy(d->element_color);

  free(d);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_defaults_s *design_defaults_copy(design_defaults_s *d)
{
  design_defaults_s *nd;

    // Sanity check parameters.
  assert(d);

  nd = design_defaults_create();
  memcpy(nd, d, sizeof(design_defaults_s));

  if (d->line_style) nd->line_style = strdup(d->line_style);
  if (d->fill_style) nd->fill_style = strdup(d->fill_style);

  if (d->background_color) nd->background_color = color_copy(d->background_color);
  if (d->element_color) nd->element_color = color_copy(d->element_color);

    // Return RETVAL
  return nd;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_push(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);

  if (!_g_list)
  {
    design_defaults_init();
    if (!_g_list) return;
  }

  list_push(_g_list, (void *)d);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_defaults_s *design_defaults_pop(void)
{
  if (!_g_list) return NULL;

    // Return RETVAL
  return list_pop(_g_list);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_defaults_s *design_defaults_current(void)
{
  if (!_g_list)
  {
    design_defaults_init();
    if (!_g_list) return NULL;
  }

    // Return RETVAL
  return (design_defaults_s *)list_curr(_g_list);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

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
                         color_s *element_color)
{
    // Sanity check parameters.
  assert(d);
  assert(line_style);
  assert(background_color);
  assert(element_color);

  design_defaults_set_units(d, units);
  design_defaults_set_line_weight(d, line_weight);
  design_defaults_set_line_style(d, line_style);
  design_defaults_set_fill_style(d, fill_style);
  design_defaults_set_dimension_text_size(d, dimension_text_size);
  design_defaults_set_dimension_precision(d, dimension_precision);
  design_defaults_set_angular_gap(d, angular_gap);
  design_defaults_set_angular_extension(d, angular_extension);
  design_defaults_set_linear_gap(d, linear_gap);
  design_defaults_set_linear_extension_above(d, linear_extension_above);
  design_defaults_set_linear_extension_below(d, linear_extension_below);
  design_defaults_set_tolerance_text_size(d, tolerance_text_size);
  design_defaults_set_tolerance_plus(d, tolerance_plus);
  design_defaults_set_tolerance_minus(d, tolerance_minus);
  design_defaults_set_tolerance_precision(d, tolerance_precision);
  design_defaults_set_background_color(d, background_color);
  design_defaults_set_element_color(d, element_color);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

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
                         color_s **element_color)
{
    // Sanity check parameters.
  assert(d);
  assert(units);
  assert(line_weight);
  assert(line_style);
  assert(fill_style);
  assert(dimension_text_size);
  assert(dimension_precision);
  assert(angular_gap);
  assert(angular_extension);
  assert(linear_gap);
  assert(linear_extension_above);
  assert(linear_extension_below);
  assert(tolerance_text_size);
  assert(tolerance_plus);
  assert(tolerance_minus);
  assert(tolerance_precision);
  assert(background_color);
  assert(element_color);

  *units = design_defaults_get_units(d);
  *line_weight = design_defaults_get_line_weight(d);
  *line_style = design_defaults_get_line_style(d);
  *fill_style = design_defaults_get_fill_style(d);
  *dimension_text_size = design_defaults_get_dimension_text_size(d);
  *dimension_precision = design_defaults_get_dimension_precision(d);
  *angular_gap = design_defaults_get_angular_gap(d);
  *angular_extension = design_defaults_get_angular_extension(d);
  *linear_gap = design_defaults_get_linear_gap(d);
  *linear_extension_above = design_defaults_get_linear_extension_above(d);
  *linear_extension_below = design_defaults_get_linear_extension_below(d);
  *tolerance_text_size = design_defaults_get_tolerance_text_size(d);
  *tolerance_plus = design_defaults_get_tolerance_plus(d);
  *tolerance_minus = design_defaults_get_tolerance_minus(d);
  *tolerance_precision = design_defaults_get_tolerance_precision(d);
  *background_color = design_defaults_get_background_color(d);
  *element_color = design_defaults_get_element_color(d);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_units(design_defaults_s *d, units_t units)
{
    // Sanity check parameters.
  assert(d);
  d->units = units;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

units_t design_defaults_get_units(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->units;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_line_weight(design_defaults_s *d, double line_weight)
{
    // Sanity check parameters.
  assert(d);
  d->line_weight = line_weight;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_line_weight(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->line_weight;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_line_style(design_defaults_s *d, char *line_style)
{
    // Sanity check parameters.
  assert(d);
  if (d->line_style) free(d->line_style);
  d->line_style = strdup(line_style);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

char *design_defaults_get_line_style(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->line_style;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_fill_style(design_defaults_s *d, char *fill_style)
{
    // Sanity check parameters.
  assert(d);
  if (d->fill_style) free(d->fill_style);
  d->fill_style = strdup(fill_style);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

char *design_defaults_get_fill_style(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->fill_style;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_dimension_text_size(design_defaults_s *d, double size)
{
    // Sanity check parameters.
  assert(d);
  d->dimension_text_size = size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_dimension_text_size(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->dimension_text_size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_dimension_precision(design_defaults_s *d, int precision)
{
    // Sanity check parameters.
  assert(d);
  d->dimension_precision = precision;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int design_defaults_get_dimension_precision(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->dimension_precision;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_angular_gap(design_defaults_s *d, double gap)
{
    // Sanity check parameters.
  assert(d);
  d->angular_gap = gap;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_angular_gap(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->angular_gap;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_angular_extension(design_defaults_s *d, double extension)
{
    // Sanity check parameters.
  assert(d);
  d->angular_extension = extension;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_angular_extension(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->angular_extension;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_linear_gap(design_defaults_s *d, double gap)
{
    // Sanity check parameters.
  assert(d);
  d->linear_gap = gap;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_linear_gap(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->linear_gap;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_linear_extension_above(design_defaults_s *d,
                                                double extension)
{
    // Sanity check parameters.
  assert(d);
  d->linear_extension_above = extension;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_linear_extension_above(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->linear_extension_above;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_linear_extension_below(design_defaults_s *d,
                                                double extension)
{
    // Sanity check parameters.
  assert(d);
  d->linear_extension_below = extension;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_linear_extension_below(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->linear_extension_below;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_tolerance_text_size(design_defaults_s *d, double size)
{
    // Sanity check parameters.
  assert(d);
  d->tolerance_text_size = size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_tolerance_text_size(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->tolerance_text_size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_tolerance_plus(design_defaults_s *d, double plus)
{
    // Sanity check parameters.
  assert(d);
  d->tolerance_plus = plus;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_tolerance_plus(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->tolerance_plus;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_tolerance_minus(design_defaults_s *d, double minus)
{
    // Sanity check parameters.
  assert(d);
  d->tolerance_minus = minus;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_defaults_get_tolerance_minus(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->tolerance_minus;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_tolerance_precision(design_defaults_s *d, int precision)
{
    // Sanity check parameters.
  assert(d);
  d->tolerance_precision = precision;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

int design_defaults_get_tolerance_precision(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->tolerance_precision;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_background_color(design_defaults_s *d, color_s *color)
{
    // Sanity check parameters.
  assert(d);
  assert(color);
  if (d->background_color) color_destroy(d->background_color);
  d->background_color = color;
  color_set_tag(d->background_color, "background-color");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

color_s *design_defaults_get_background_color(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->background_color;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_defaults_set_element_color(design_defaults_s *d, color_s *color)
{
    // Sanity check parameters.
  assert(d);
  assert(color);
  if (d->element_color) color_destroy(d->element_color);
  d->element_color = color;
  color_set_tag(d->element_color, "element-color");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

color_s *design_defaults_get_element_color(design_defaults_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->element_color;
}

