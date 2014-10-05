#ifndef DESIGN_POLYLINE_XML_H
#define DESIGN_POLYLINE_XML_H

#include "design-polyline.h"

xmlDocPtr design_polyline_to_xml_doc(design_polyline_s *pl);
xmlNodePtr design_polyline_to_xml_node(design_polyline_s *pl);
xmlNodePtr design_polyline_root_node(xmlDocPtr doc);
design_polyline_s *design_polyline_from_xml_doc(xmlDocPtr doc);
design_polyline_s *design_polyline_from_xml_node(xmlNodePtr node);
design_polyline_s *design_polyline_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_POLYLINE_XML_H
