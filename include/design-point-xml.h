#ifndef DESIGN_POINT_XML_H
#define DESIGN_POINT_XML_H

#include "vertex-xml.h"

#include "design-point.h"

xmlDocPtr design_point_to_xml_doc(design_point_s *p);
xmlNodePtr design_point_to_xml_node(design_point_s *p);
xmlNodePtr design_point_root_node(xmlDocPtr doc);
design_point_s *design_point_from_xml_doc(xmlDocPtr doc);
design_point_s *design_point_from_xml_node(xmlNodePtr node);
design_point_s *design_point_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_POINT_XML_H
