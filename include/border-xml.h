/*!
    @file border-xml.h

    @brief HEADER_BRIEF

    @timestamp Tue, 11 Nov 2014 07:22:32 +0000

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

    @file border-xml.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef BORDER_XML_H
#define BORDER_XML_H

#include "border.h"

#include "color-xml.h"

#include "margins-xml.h"

xmlDocPtr border_to_xml_doc(border_s *b);
xmlNodePtr border_to_xml_node(border_s *b);
xmlNodePtr border_root_node(xmlDocPtr doc);
border_s *border_from_xml_doc(xmlDocPtr doc);
border_s *border_from_xml_node(xmlNodePtr node);
border_s *border_sieve(FILE *infile, FILE *outfile);

#endif // BORDER_XML_H
