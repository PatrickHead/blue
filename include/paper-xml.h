/*!
    @file paper-xml.h

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

    @file paper-xml.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef PAPER_XML_H
#define PAPER_XML_H

#include "paper.h"

#include "color-xml.h"

#include "margins-xml.h"

xmlDocPtr paper_to_xml_doc(paper_s *p);
xmlNodePtr paper_to_xml_node(paper_s *p);
xmlNodePtr paper_root_node(xmlDocPtr doc);
paper_s *paper_from_xml_doc(xmlDocPtr doc);
paper_s *paper_from_xml_node(xmlNodePtr node);
paper_s *paper_sieve(FILE *infile, FILE *outfile);

#endif // PAPER_XML_H
