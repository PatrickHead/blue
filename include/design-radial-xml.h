#ifndef DESIGN_RADIAL_XML_H
#define DESIGN_RADIAL_XML_H

#include "vertex-xml.h"

#include "design-radial.h"

xmlDocPtr design_radial_to_xml_doc(design_radial_s *r);
xmlNodePtr design_radial_to_xml_node(design_radial_s *r);
xmlNodePtr design_radial_root_node(xmlDocPtr doc);
design_radial_s *design_radial_from_xml_doc(xmlDocPtr doc);
design_radial_s *design_radial_from_xml_node(xmlNodePtr node);
design_radial_s *design_radial_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_RADIAL_XML_H
