#ifndef MARGINS_XML_H
#define MARGINS_XML_H

#include "margins.h"

xmlDocPtr margins_to_xml_doc(margins_s *m);
xmlNodePtr margins_root_node(xmlDocPtr doc);
xmlNodePtr margins_to_xml_node(margins_s *m);
margins_s *margins_from_xml_doc(xmlDocPtr doc);
margins_s *margins_from_xml_node(xmlNodePtr node);
margins_s *margins_sieve(FILE *infile, FILE *outfile);

#endif // MARGINS_XML_H
