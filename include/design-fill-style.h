/*!
    @file design-fill-style.h

    @brief Header file for design fill style structure

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

    @file design-fill-style.h

    @brief Header file for design fill style structure

    Structure and maintenance functions for design fill style.

  */

#ifndef DESIGN_FILL_STYLE_H
#define DESIGN_FILL_STYLE_H

  // External include files

#include "color.h"

  // Project specific include files

#include "design-fill-style-type.h"

  /*!
    @brief Design fill style structure
  */

typedef struct
{
    /*! @brief Unique name of fill style */
  char *name;
    /*! @brief Fill style type */
  design_fill_style_t type;
    /*! @brief Width of drawn lines in fill style, if any */
  double line_weight;
    /*! @brief Style of drawn lines in fill style, if any */
  char *line_style;
    /*! @brief Background color of filled area */
  color_s *background_color;
    /*! @brief Color of drawn lines in fill style, if any */
  color_s *pattern_color;
    /*! @brief Angle from vertical of first set of lines, if any */
  double angle1;
    /*! @brief Line spacing of first set of lines, if any */
  double spacing1;
    /*! @brief Angle from vertical of second set of lines, if any */
  double angle2;
    /*! @brief Line spacing of second set of lines, if any */
  double spacing2;
    /*! @brief ELEMENT_BRIEF */
  char *source;
} design_fill_style_s;

  // Structure maintenance functions

design_fill_style_s *design_fill_style_create(void);
void design_fill_style_destroy_void(void *v);
void design_fill_style_destroy(design_fill_style_s *fs);
design_fill_style_s *design_fill_style_copy(design_fill_style_s *fs);

  // Comprehensive getter/setter

void design_fill_style_set(design_fill_style_s *fs,
                           char *name,
                           design_fill_style_t type,
                           double line_weight,
                           char *line_style,
                           color_s *background_color,
                           color_s *pattern_color,
                           double angle1,
                           double spacing1,
                           double angle2,
                           double spacing2,
                           char *source);
void design_fill_style_get(design_fill_style_s *fs,
                           char **name,
                           design_fill_style_t *type,
                           double *line_weight,
                           char **line_style,
                           color_s **background_color,
                           color_s **pattern_color,
                           double *angle1,
                           double *spacing1,
                           double *angle2,
                           double *spacing2,
                           char **source);

  // Individual getters/setters

void design_fill_style_set_name(design_fill_style_s *fs, char *name);
char *design_fill_style_get_name(design_fill_style_s *fs);

void design_fill_style_set_type(design_fill_style_s *fs,
                                design_fill_style_t type);
design_fill_style_t design_fill_style_get_type(design_fill_style_s *fs);

void design_fill_style_set_line_weight(design_fill_style_s *fs,
                                       double line_weight);
double design_fill_style_get_line_weight(design_fill_style_s *fs);

void design_fill_style_set_line_style(design_fill_style_s *fs,
                                      char *line_style);
char *design_fill_style_get_line_style(design_fill_style_s *fs);

void design_fill_style_set_background_color(design_fill_style_s *fs,
                                            color_s *background_color);
color_s *design_fill_style_get_background_color(design_fill_style_s *fs);

void design_fill_style_set_pattern_color(design_fill_style_s *fs,
                                         color_s *pattern_color);
color_s *design_fill_style_get_pattern_color(design_fill_style_s *fs);

void design_fill_style_set_angle1(design_fill_style_s *fs, double angle);
double design_fill_style_get_angle1(design_fill_style_s *fs);

void design_fill_style_set_spacing1(design_fill_style_s *fs, double spacing);
double design_fill_style_get_spacing1(design_fill_style_s *fs);

void design_fill_style_set_angle2(design_fill_style_s *fs, double angle);
double design_fill_style_get_angle2(design_fill_style_s *fs);

void design_fill_style_set_spacing2(design_fill_style_s *fs, double spacing);
double design_fill_style_get_spacing2(design_fill_style_s *fs);

void design_fill_style_set_source(design_fill_style_s *fs, char *source);
char *design_fill_style_get_source(design_fill_style_s *fs);

#endif // DESIGN_FILL_STYLE_H
