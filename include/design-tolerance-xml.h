#ifndef DESIGN_TOLERANCE_XML_H
#define DESIGN_TOLERANCE_XML_H

#include "vertex-xml.h"

#include "design-tolerance.h"

xmlDocPtr design_tolerance_to_xml_doc(design_tolerance_s *t);
xmlNodePtr design_tolerance_to_xml_node(design_tolerance_s *t);
xmlNodePtr design_tolerance_root_node(xmlDocPtr doc);
design_tolerance_s *design_tolerance_from_xml_doc(xmlDocPtr doc);
design_tolerance_s *design_tolerance_from_xml_node(xmlNodePtr node);
design_tolerance_s *design_tolerance_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_TOLERANCE_XML_H
