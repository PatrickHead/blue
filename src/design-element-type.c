/*!
    @file design-element-type.c

    @brief SOURCE_BRIEF

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

    @file design-element-type.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-element-type.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_element_t str2design_element_type(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "dimension")) return design_element_type_dimension;
  if (!strcmp(s, "elliptic")) return design_element_type_elliptic;
  if (!strcmp(s, "line")) return design_element_type_line;
  if (!strcmp(s, "point")) return design_element_type_point;
  if (!strcmp(s, "polyline")) return design_element_type_polyline;
  if (!strcmp(s, "spline")) return design_element_type_spline;
  if (!strcmp(s, "text")) return design_element_type_text;
  if (!strcmp(s, "tolerance")) return design_element_type_tolerance;

    // Return RETVAL
  return design_element_type_END;
}

const char* design_element_type2str(design_element_t t)
{
  switch (t)
  {
    case design_element_type_dimension: return "dimension";
    case design_element_type_elliptic: return "elliptic";
    case design_element_type_line: return "line";
    case design_element_type_point: return "point";
    case design_element_type_polyline: return "polyline";
    case design_element_type_spline: return "spline";
    case design_element_type_text: return "text";
    case design_element_type_tolerance: return "tolerance";
    case design_element_type_END: return "UNKNOWN";
  }

    // Return RETVAL
  return "UNKNOWN";
}

