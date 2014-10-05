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
