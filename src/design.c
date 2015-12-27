/*!
    @file design.c

    @brief SOURCE_BRIEF

    @timestamp Sun, 27 Dec 2015 07:07:05 +0000

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

    @file design.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-defaults.h"

#include "design.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_s *design_create(void)
{
  design_s *d;

  d = (design_s *)malloc(sizeof(design_s));
  memset(d, 0, sizeof(design_s));

  d->defaults = design_defaults_create();
  d->line_styles = design_line_styles_create();
  d->fill_styles = design_fill_styles_create();
  d->layers = design_layers_create();
  d->scaling_factor = 0.0;

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

void design_destroy(design_s *d)
{
    // Sanity check parameters.
  assert(d);

  if (d->defaults) design_defaults_destroy(d->defaults);
  if (d->line_styles) design_line_styles_destroy(d->line_styles);
  if (d->fill_styles) design_fill_styles_destroy(d->fill_styles);
  if (d->layers) design_layers_destroy(d->layers);

  free(d);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_s *design_copy(design_s *d)
{
  design_s *nd;

    // Sanity check parameters.
  assert(d);

  nd = design_create();
  memcpy(nd, d, sizeof(design_s));

  if (d->defaults) nd->defaults = design_defaults_copy(d->defaults);
  if (d->line_styles) nd->line_styles = design_line_styles_copy(d->line_styles);
  if (d->fill_styles) nd->fill_styles = design_fill_styles_copy(d->fill_styles);
  if (d->layers) nd->layers = design_layers_copy(d->layers);

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

void design_set(design_s *d,
                design_defaults_s *defaults,
                design_line_styles_s *line_styles,
                design_fill_styles_s *fill_styles,
                design_layers_s *layers,
                double scaling_factor)
{
    // Sanity check parameters.
  assert(d);
  assert(defaults);
  assert(line_styles);
  assert(fill_styles);
  assert(layers);

  design_set_defaults(d, defaults);
  design_set_line_styles(d, line_styles);
  design_set_fill_styles(d, fill_styles);
  design_set_layers(d, layers);
  design_set_scaling_factor(d, scaling_factor);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_get(design_s *d,
                design_defaults_s **defaults,
                design_line_styles_s **line_styles,
                design_fill_styles_s **fill_styles,
                design_layers_s **layers,
                double *scaling_factor)
{
    // Sanity check parameters.
  assert(d);
  assert(defaults);
  assert(line_styles);
  assert(fill_styles);
  assert(layers);

  *defaults = design_get_defaults(d);
  *line_styles = design_get_line_styles(d);
  *fill_styles = design_get_fill_styles(d);
  *layers = design_get_layers(d);
  *scaling_factor = design_get_scaling_factor(d);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_set_defaults(design_s *d, design_defaults_s *dflts)
{
    // Sanity check parameters.
  assert(d);
  assert(dflts);

  if (d->defaults) design_defaults_destroy(d->defaults);
  d->defaults = design_defaults_copy(dflts);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_defaults_s *design_get_defaults(design_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->defaults;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_set_line_styles(design_s *d, design_line_styles_s *lss)
{
    // Sanity check parameters.
  assert(d);
  assert(lss);

  if (d->line_styles) design_line_styles_destroy(d->line_styles);
  d->line_styles = design_line_styles_copy(lss);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_line_styles_s *design_get_line_styles(design_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->line_styles;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_set_fill_styles(design_s *d, design_fill_styles_s *lss)
{
    // Sanity check parameters.
  assert(d);
  assert(lss);

  if (d->fill_styles) design_fill_styles_destroy(d->fill_styles);
  d->fill_styles = design_fill_styles_copy(lss);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_styles_s *design_get_fill_styles(design_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->fill_styles;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_set_layers(design_s *d, design_layers_s *ls)
{
    // Sanity check parameters.
  assert(d);
  assert(ls);

  if (d->layers) design_layers_destroy(d->layers);
  d->layers = design_layers_copy(ls);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_layers_s *design_get_layers(design_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->layers;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void design_set_scaling_factor(design_s *d, double sf)
{
    // Sanity check parameters.
  assert(d);

  d->scaling_factor = sf;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double design_get_scaling_factor(design_s *d)
{
    // Sanity check parameters.
  assert(d);
    // Return RETVAL
  return d->scaling_factor;
}

