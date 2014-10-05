#ifndef DESIGN_TEXT_XML_H
#define DESIGN_TEXT_XML_H

#include "vertex-xml.h"

#include "design-text.h"

xmlDocPtr design_text_to_xml_doc(design_text_s *t);
xmlNodePtr design_text_to_xml_node(design_text_s *t);
xmlNodePtr design_text_root_node(xmlDocPtr doc);
design_text_s *design_text_from_xml_doc(xmlDocPtr doc);
design_text_s *design_text_from_xml_node(xmlNodePtr node);
design_text_s *design_text_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_TEXT_XML_H
