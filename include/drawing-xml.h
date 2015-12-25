/*!
    @file drawing-xml.h

    @brief HEADER_BRIEF

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

    @file drawing-xml.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DRAWING_XML_H
#define DRAWING_XML_H

#include "drawing.h"

xmlDocPtr drawing_to_xml_doc(drawing_s *d);
xmlNodePtr drawing_to_xml_node(drawing_s *d);
xmlNodePtr drawing_root_node(xmlDocPtr doc);
drawing_s *drawing_from_xml_doc(xmlDocPtr doc);
drawing_s *drawing_from_xml_node(xmlNodePtr node);
drawing_s *drawing_sieve(FILE *infile, FILE *outfile);

#endif // DRAWING_XML_H
