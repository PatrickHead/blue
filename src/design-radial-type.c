/*!
    @file design-radial-type.c

    @brief SOURCE_BRIEF

    @timestamp Mon, 06 Jan 2014 15:17:36 +0000

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

    @file design-radial-type.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-radial-type.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_radial_t str2design_radial_type(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "radius")) return design_radial_type_radius;
  if (!strcmp(s, "diameter")) return design_radial_type_diameter;

    // Return RETVAL
  return design_radial_type_radius;
}

const char* design_radial_type2str(design_radial_t t)
{
  switch (t)
  {
    case design_radial_type_radius: return "radius";
    case design_radial_type_diameter: return "diameter";
  }

    // Return RETVAL
  return "UNKNOWN";
}

