/*!
    @file title-block-xml.h

    @brief HEADER_BRIEF

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

    @file title-block-xml.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef TITLE_BLOCK_XML_H
#define TITLE_BLOCK_XML_H

#include "title-block.h"

#include "color-xml.h"

xmlDocPtr title_block_to_xml_doc(title_block_s *tb);
xmlNodePtr title_block_to_xml_node(title_block_s *tb);
xmlNodePtr title_block_root_node(xmlDocPtr doc);
title_block_s *title_block_from_xml_doc(xmlDocPtr node);
title_block_s *title_block_from_xml_node(xmlNodePtr node);
title_block_s *title_block_sieve(FILE *infile, FILE *outfile);

#endif // TITLE_BLOCK_XML_H
