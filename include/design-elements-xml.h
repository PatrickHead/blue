#ifndef DESIGN_ELEMENTS_XML_H
#define DESIGN_ELEMENTS_XML_H

#include "design-elements.h"

#include "design-element-xml.h"

xmlDocPtr design_elements_to_xml_doc(design_elements_s *es);
xmlNodePtr design_elements_to_xml_node(design_elements_s *es);
xmlNodePtr design_elements_root_node(xmlDocPtr doc);
design_elements_s *design_elements_from_xml_doc(xmlDocPtr doc);
design_elements_s *design_elements_from_xml_node(xmlNodePtr node);
design_elements_s *design_elements_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_ELEMENTS_XML_H
