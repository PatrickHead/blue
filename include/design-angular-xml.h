/*!
    @file design-angular-xml.h

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

    @file design-angular-xml.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef DESIGN_ANGULAR_XML_H
#define DESIGN_ANGULAR_XML_H

#include "vertex-xml.h"

#include "design-angular.h"

xmlDocPtr design_angular_to_xml_doc(design_angular_s *a);
xmlNodePtr design_angular_to_xml_node(design_angular_s *a);
xmlNodePtr design_angular_root_node(xmlDocPtr doc);
design_angular_s *design_angular_from_xml_doc(xmlDocPtr doc);
design_angular_s *design_angular_from_xml_node(xmlNodePtr node);
design_angular_s *design_angular_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_ANGULAR_XML_H
