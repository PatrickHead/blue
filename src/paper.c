/*!
    @file paper.c

    @brief SOURCE_BRIEF

    @timestamp Sun, 27 Dec 2015 08:20:57 +0000

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

    @file paper.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <assert.h>

  // Project related headers

#include "paper.h"

static void dimensions(paper_s *paper);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

paper_s *paper_create(void)
{
  paper_s *p;

  p = (paper_s *)malloc(sizeof(paper_s));
  memset(p, 0, sizeof(paper_s));

  p->margins = margins_create();

  p->size = paper_size_type_iso_a4;
  p->orientation = paper_orientation_type_portrait;
  dimensions(p);

  margins_set_units(p->margins, p->units);

  p->color = color_create();
  color_set_tag(p->color, "color");
  color_white(p->color);

    // Return RETVAL
  return p;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_destroy(paper_s *p)
{
    // Sanity check parameters.
  assert(p);
  if (p->margins) margins_destroy(p->margins);
  if (p->color) color_destroy(p->color);
  free(p);
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

paper_s *paper_copy(paper_s *p)
{
  paper_s *np;

    // Sanity check parameters.
  assert(p);

  np = paper_create();
  memcpy(np, p, sizeof(paper_s));

  if (p->margins) np->margins = margins_copy(p->margins);
  if (p->color) np->color = color_copy(p->color);

    // Return RETVAL
  return np;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_set(paper_s *p,
               units_t units,
               paper_size_t size,
               paper_orientation_t orientation,
               margins_s *margins,
               double width,
               double height,
               color_s *color)
{
    // Sanity check parameters.
  assert(p);
  assert(margins);
  assert(color);

  paper_set_units(p, units);
  paper_set_size(p, size);
  paper_set_orientation(p, orientation);
  paper_set_margins(p, margins);
  paper_set_width(p, width);
  paper_set_height(p, height);
  paper_set_color(p, color);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_get(paper_s *p,
               units_t *units,
               paper_size_t *size,
               paper_orientation_t *orientation,
               margins_s **margins,
               double *width,
               double *height,
               color_s **color)
{
    // Sanity check parameters.
  assert(p);
  assert(units);
  assert(size);
  assert(orientation);
  assert(margins);
  assert(width);
  assert(height);
  assert(color);

  *units = paper_get_units(p);
  *size = paper_get_size(p);
  *orientation = paper_get_orientation(p);
  *margins = paper_get_margins(p);
  *width = paper_get_width(p);
  *height = paper_get_height(p);
  *color = paper_get_color(p);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_set_units(paper_s *p, units_t ut)
{
    // Sanity check parameters.
  assert(p);
  p->units = ut;
  dimensions(p);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

units_t paper_get_units(paper_s *p)
{
    // Sanity check parameters.
  assert(p);
    // Return RETVAL
  return p->units;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_set_size(paper_s *p, paper_size_t st)
{
    // Sanity check parameters.
  assert(p);
  p->size = st;
  dimensions(p);
  switch (p->size)
  {
    case paper_size_type_iso_a0:
    case paper_size_type_iso_a1:
    case paper_size_type_iso_a2:
    case paper_size_type_iso_a3:
    case paper_size_type_iso_a4:
      margins_set_units(p->margins, p->units);
      break;
    case paper_size_type_ansi_a:
    case paper_size_type_ansi_b:
    case paper_size_type_ansi_c:
    case paper_size_type_ansi_d:
    case paper_size_type_ansi_e:
    case paper_size_type_arch_a:
    case paper_size_type_arch_b:
    case paper_size_type_arch_c:
    case paper_size_type_arch_d:
    case paper_size_type_arch_e:
    case paper_size_type_arch_e1:
    case paper_size_type_arch_e2:
    case paper_size_type_arch_e3:
    case paper_size_type_letter:
    case paper_size_type_legal:
    case paper_size_type_tabloid:
      margins_set_units(p->margins, p->units);
      break;
    case paper_size_type_user_defined:
      break;
  }
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

paper_size_t paper_get_size(paper_s *p)
{
    // Sanity check parameters.
  assert(p);
    // Return RETVAL
  return p->size;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_set_orientation(paper_s *p, paper_orientation_t o)
{
    // Sanity check parameters.
  assert(p);
  p->orientation = o;
  dimensions(p);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

paper_orientation_t paper_get_orientation(paper_s *p)
{
    // Sanity check parameters.
  assert(p);
    // Return RETVAL
  return p->orientation;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_set_margins(paper_s *p, margins_s *m)
{
    // Sanity check parameters.
  assert(p);
  assert(m);
  if (p->margins) margins_destroy(p->margins);
  p->margins = m;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

margins_s *paper_get_margins(paper_s *p)
{
    // Sanity check parameters.
  assert(p);
    // Return RETVAL
  return p->margins;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_set_width(paper_s *p, double width)
{
    // Sanity check parameters.
  assert(p);
  p->width = width;
  paper_set_size(p, paper_size_type_user_defined);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double paper_get_width(paper_s *p)
{
    // Sanity check parameters.
  assert(p);
    // Return RETVAL
  return p->width;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_set_height(paper_s *p, double height)
{
    // Sanity check parameters.
  assert(p);
  p->height = height;
  paper_set_size(p, paper_size_type_user_defined);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double paper_get_height(paper_s *p)
{
    // Sanity check parameters.
  assert(p);
    // Return RETVAL
  return p->height;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void paper_set_color(paper_s *p, color_s *color)
{
    // Sanity check parameters.
  assert(p);
  assert(color);
  if (p->color) color_destroy(p->color);
  p->color = color_copy(color);
  color_set_tag(p->color, "color");
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

color_s *paper_get_color(paper_s *p)
{
    // Sanity check parameters.
  assert(p);
    // Return RETVAL
  return p->color;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

char* paper_size2str(paper_size_t type)
{
  switch (type)
  {
    case paper_size_type_iso_a0: return "iso-a0";
    case paper_size_type_iso_a1: return "iso-a1";
    case paper_size_type_iso_a2: return "iso-a2";
    case paper_size_type_iso_a3: return "iso-a3";
    case paper_size_type_iso_a4: return "iso-a4";
    case paper_size_type_ansi_a: return "ansi-a";
    case paper_size_type_ansi_b: return "ansi-b";
    case paper_size_type_ansi_c: return "ansi-c";
    case paper_size_type_ansi_d: return "ansi-d";
    case paper_size_type_ansi_e: return "ansi-e";
    case paper_size_type_arch_a: return "arch-a";
    case paper_size_type_arch_b: return "arch-b";
    case paper_size_type_arch_c: return "arch-c";
    case paper_size_type_arch_d: return "arch-d";
    case paper_size_type_arch_e: return "arch-e";
    case paper_size_type_arch_e1: return "arch-e1";
    case paper_size_type_arch_e2: return "arch-e2";
    case paper_size_type_arch_e3: return "arch-e3";
    case paper_size_type_letter: return "letter";
    case paper_size_type_legal: return "legal";
    case paper_size_type_tabloid: return "tabloid";
    case paper_size_type_user_defined: return "user-defined";
  }

    // Return RETVAL
  return "iso-a1";
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

paper_size_t str2paper_size(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "iso-a0")) return paper_size_type_iso_a0;
  if (!strcmp(s, "iso-a1")) return paper_size_type_iso_a1;
  if (!strcmp(s, "iso-a2")) return paper_size_type_iso_a2;
  if (!strcmp(s, "iso-a3")) return paper_size_type_iso_a3;
  if (!strcmp(s, "iso-a4")) return paper_size_type_iso_a4;
  if (!strcmp(s, "ansi-a")) return paper_size_type_ansi_a;
  if (!strcmp(s, "ansi-b")) return paper_size_type_ansi_b;
  if (!strcmp(s, "ansi-c")) return paper_size_type_ansi_c;
  if (!strcmp(s, "ansi-d")) return paper_size_type_ansi_d;
  if (!strcmp(s, "ansi-e")) return paper_size_type_ansi_e;
  if (!strcmp(s, "arch-a")) return paper_size_type_arch_a;
  if (!strcmp(s, "arch-b")) return paper_size_type_arch_b;
  if (!strcmp(s, "arch-c")) return paper_size_type_arch_c;
  if (!strcmp(s, "arch-d")) return paper_size_type_arch_d;
  if (!strcmp(s, "arch-e")) return paper_size_type_arch_e;
  if (!strcmp(s, "arch-e1")) return paper_size_type_arch_e1;
  if (!strcmp(s, "arch-e2")) return paper_size_type_arch_e2;
  if (!strcmp(s, "arch-e3")) return paper_size_type_arch_e3;
  if (!strcmp(s, "letter")) return paper_size_type_letter;
  if (!strcmp(s, "legal")) return paper_size_type_legal;
  if (!strcmp(s, "tabloid")) return paper_size_type_tabloid;

    // Return RETVAL
  return paper_size_type_iso_a1;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

char* paper_orientation2str(paper_orientation_t type)
{
  switch (type)
  {
    case paper_orientation_type_portrait: return "portrait";
    case paper_orientation_type_landscape: return "landscape";
  }

    // Return RETVAL
  return "portrait";
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

paper_orientation_t str2paper_orientation(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "portrait")) return paper_orientation_type_portrait;
  if (!strcmp(s, "landscape")) return paper_orientation_type_landscape;

    // Return RETVAL
  return paper_orientation_type_portrait;
}

static void dimensions(paper_s *paper)
{
  double hold;

  switch (paper->size)
  {
    case paper_size_type_iso_a0:
      paper->width = 841.0;
      paper->height = 1189.0;
      paper->units = units_type_mm;
      break;
    case paper_size_type_iso_a1:
      paper->width = 594.0;
      paper->height = 841.0;
      paper->units = units_type_mm;
      break;
    case paper_size_type_iso_a2:
      paper->width = 420.0;
      paper->height = 594.0;
      paper->units = units_type_mm;
      break;
    case paper_size_type_iso_a3:
      paper->width = 297.0;
      paper->height = 420.0;
      paper->units = units_type_mm;
      break;
    case paper_size_type_iso_a4:
      paper->width = 210.0;
      paper->height = 297.0;
      paper->units = units_type_mm;
      break;
    case paper_size_type_ansi_a:
      paper->width = 8.5;
      paper->height = 11.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_ansi_b:
      paper->width = 11.0;
      paper->height = 17.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_ansi_c:
      paper->width = 17.0;
      paper->height = 22.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_ansi_d:
      paper->width = 22.0;
      paper->height = 34.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_ansi_e:
      paper->width = 34.0;
      paper->height = 44.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_arch_a:
      paper->width = 9.0;
      paper->height = 12.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_arch_b:
      paper->width = 12.0;
      paper->height = 18.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_arch_c:
      paper->width = 18.0;
      paper->height = 24.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_arch_d:
      paper->width = 24.0;
      paper->height = 36.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_arch_e:
      paper->width = 36.0;
      paper->height = 48.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_arch_e1:
      paper->width = 30.0;
      paper->height = 42.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_arch_e2:
      paper->width = 26.0;
      paper->height = 38.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_arch_e3:
      paper->width = 27.0;
      paper->height = 39.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_letter:
      paper->width = 8.5;
      paper->height = 11.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_legal:
      paper->width = 8.5;
      paper->height = 14.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_tabloid:
      paper->width = 11.0;
      paper->height = 17.0;
      paper->units = units_type_in;
      break;
    case paper_size_type_user_defined:
      break;
  }

  switch (paper->orientation)
  {
    case paper_orientation_type_portrait:
      break;
    case paper_orientation_type_landscape:
      hold = paper->height;
      paper->height = paper->width;
      paper->width = hold;
      break;
  }
}

