/*!
    @file design-visibility-type.c

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

    @file design-visibility-type.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-visibility-type.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_visibility_t str2design_visibility_type(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "visible")) return design_visibility_type_visible;
  if (!strcmp(s, "hidden")) return design_visibility_type_hidden;

    // Return RETVAL
  return design_visibility_type_visible;
}

const char* design_visibility_type2str(design_visibility_t t)
{
  switch (t)
  {
    case design_visibility_type_visible: return "visible";
    case design_visibility_type_hidden: return "hidden";
  }

    // Return RETVAL
  return "visible";
}

