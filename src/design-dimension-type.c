/*!
    @file design-dimension-type.c

    @brief SOURCE_BRIEF

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

    @file design-dimension-type.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-dimension-type.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_dimension_t str2design_dimension_type(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "linear")) return design_dimension_type_linear;
  if (!strcmp(s, "angular")) return design_dimension_type_angular;
  if (!strcmp(s, "radial")) return design_dimension_type_radial;

    // Return RETVAL
  return design_dimension_type_linear;
}

const char* design_dimension_type2str(design_dimension_t t)
{
  switch (t)
  {
    case design_dimension_type_linear: return "linear";
    case design_dimension_type_angular: return "angular";
    case design_dimension_type_radial: return "radial";
    default: break;
  }

    // Return RETVAL
  return "UNKNOWN";
}

