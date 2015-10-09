/*!
    @file margins.c

    @brief SOURCE_BRIEF

    @timestamp Tue, 11 Nov 2014 07:22:33 +0000

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

    @file margins.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "margins.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

margins_s *margins_create(void)
{
  margins_s *m;
  m = (margins_s *)malloc(sizeof(margins_s));
  memset(m, 0, sizeof(margins_s));
  m->units = units_type_mm;
  m->top = m->bottom = m->left = m->right = 6.35;
    // Return RETVAL
  return m;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void margins_destroy(margins_s *m)
{
    // Sanity check parameters.
  assert(m);
  free(m);
    // Return RETVAL
  return;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

margins_s *margins_copy(margins_s *m)
{
  margins_s *nm;

    // Sanity check parameters.
  assert(m);

  nm = margins_create();
  memcpy(nm, m, sizeof(margins_s));

    // Return RETVAL
  return nm;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void margins_set(margins_s *m,
                 units_t units,
                 double left,
                 double right,
                 double top,
                 double bottom)
{
    // Sanity check parameters.
  assert(m);

  margins_set_units(m, units);
  margins_set_left(m, left);
  margins_set_right(m, right);
  margins_set_top(m, top);
  margins_set_bottom(m, bottom);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void margins_get(margins_s *m,
                 units_t *units,
                 double *left,
                 double *right,
                 double *top,
                 double *bottom)
{
    // Sanity check parameters.
  assert(m);
  assert(units);
  assert(left);
  assert(right);
  assert(top);
  assert(bottom);

  *units = margins_get_units(m);
  *left = margins_get_left(m);
  *right = margins_get_right(m);
  *top = margins_get_top(m);
  *bottom = margins_get_bottom(m);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void margins_set_units(margins_s *m, units_t u)
{
  units_t old_type;

    // Sanity check parameters.
  assert(m);

  old_type = m->units;

  m->units = u;
  m->top = units_convert(m->top, old_type, m->units);
  m->bottom = units_convert(m->bottom, old_type, m->units);
  m->left = units_convert(m->left, old_type, m->units);
  m->right = units_convert(m->right, old_type, m->units);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

units_t margins_get_units(margins_s *m)
{
    // Sanity check parameters.
  assert(m);
    // Return RETVAL
  return m->units;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void margins_set_left(margins_s *m, double l)
{
    // Sanity check parameters.
  assert(m);
  m->left = l;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double margins_get_left(margins_s *m)
{
    // Sanity check parameters.
  assert(m);
    // Return RETVAL
  return m->left;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void margins_set_right(margins_s *m, double r)
{
    // Sanity check parameters.
  assert(m);
  m->right = r;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double margins_get_right(margins_s *m)
{
    // Sanity check parameters.
  assert(m);
    // Return RETVAL
  return m->right;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void margins_set_top(margins_s *m, double t)
{
    // Sanity check parameters.
  assert(m);
  m->top = t;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double margins_get_top(margins_s *m)
{
    // Sanity check parameters.
  assert(m);
    // Return RETVAL
  return m->top;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void margins_set_bottom(margins_s *m, double b)
{
    // Sanity check parameters.
  assert(m);
  m->bottom = b;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double margins_get_bottom(margins_s *m)
{
    // Sanity check parameters.
  assert(m);
    // Return RETVAL
  return m->bottom;
}

