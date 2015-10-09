/*!
    @file design-fill-style-type.c

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

    @file design-fill-style-type.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-fill-style-type.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_fill_style_t str2design_fill_style_type(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "line")) return design_fill_style_type_line;
  if (!strcmp(s, "hatch")) return design_fill_style_type_hatch;
  if (!strcmp(s, "stipple")) return design_fill_style_type_stipple;
  if (!strcmp(s, "source-only")) return design_fill_style_type_source_only;

    // Return RETVAL
  return design_fill_style_type_line;
}

const char* design_fill_style_type2str(design_fill_style_t t)
{
  switch (t)
  {
    case design_fill_style_type_line: return "line";
    case design_fill_style_type_hatch: return "hatch";
    case design_fill_style_type_stipple: return "stipple";
    case design_fill_style_type_source_only: return "source-only";
  }

    // Return RETVAL
  return "UNKNOWN";
}

