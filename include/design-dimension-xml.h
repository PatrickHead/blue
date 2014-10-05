#ifndef DESIGN_DIMENSION_XML_H
#define DESIGN_DIMENSION_XML_H

#include "design-dimension.h"
#include "design-angular-xml.h"
#include "design-linear-xml.h"
#include "design-radial-xml.h"

xmlDocPtr design_dimension_to_xml_doc(design_dimension_s *d);
xmlNodePtr design_dimension_to_xml_node(design_dimension_s *d);
xmlNodePtr design_dimension_root_node(xmlDocPtr doc);
design_dimension_s *design_dimension_from_xml_doc(xmlDocPtr doc);
design_dimension_s *design_dimension_from_xml_node(xmlNodePtr node);
design_dimension_s *design_dimension_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_DIMENSION_XML_H
