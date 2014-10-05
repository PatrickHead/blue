#ifndef DESIGN_SPLINE_XML_H
#define DESIGN_SPLINE_XML_H

#include "design-spline.h"

xmlDocPtr design_spline_to_xml_doc(design_spline_s *s);
xmlNodePtr design_spline_to_xml_node(design_spline_s *s);
xmlNodePtr design_spline_root_node(xmlDocPtr doc);
design_spline_s *design_spline_from_xml_doc(xmlDocPtr doc);
design_spline_s *design_spline_from_xml_node(xmlNodePtr node);
design_spline_s *design_spline_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_SPLINE_XML_H
