#ifndef DESIGN_LINE_XML_H
#define DESIGN_LINE_XML_H

#include "vertex-xml.h"

#include "design-line.h"

xmlDocPtr design_line_to_xml_doc(design_line_s *l);
xmlNodePtr design_line_to_xml_node(design_line_s *l);
xmlNodePtr design_line_root_node(xmlDocPtr doc);
design_line_s *design_line_from_xml_doc(xmlDocPtr doc);
design_line_s *design_line_from_xml_node(xmlNodePtr node);
design_line_s *design_line_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_LINE_XML_H
