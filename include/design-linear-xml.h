#ifndef DESIGN_LINEAR_XML_H
#define DESIGN_LINEAR_XML_H

#include "vertex-xml.h"

#include "design-linear.h"

xmlDocPtr design_linear_to_xml_doc(design_linear_s *l);
xmlNodePtr design_linear_to_xml_node(design_linear_s *l);
xmlNodePtr design_linear_root_node(xmlDocPtr doc);
design_linear_s *design_linear_from_xml_doc(xmlDocPtr doc);
design_linear_s *design_linear_from_xml_node(xmlNodePtr node);
design_linear_s *design_linear_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_LINEAR_XML_H
