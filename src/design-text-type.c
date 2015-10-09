/*!
    @file design-text-type.c

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

    @file design-text-type.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <string.h>
#include <assert.h>

  // Project related headers

#include "design-text-type.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

design_text_t str2design_text_type(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "drawing")) return design_text_type_drawing;
  if (!strcmp(s, "annotation")) return design_text_type_annotation;

    // Return RETVAL
  return design_text_type_drawing;
}

const char* design_text_type2str(design_text_t t)
{
  switch (t)
  {
    case design_text_type_drawing: return "drawing";
    case design_text_type_annotation: return "annotation";
  }

    // Return RETVAL
  return "UNKNOWN";
}

