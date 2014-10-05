#ifndef DESIGN_ANGULAR_XML_H
#define DESIGN_ANGULAR_XML_H

#include "vertex-xml.h"

#include "design-angular.h"

xmlDocPtr design_angular_to_xml_doc(design_angular_s *a);
xmlNodePtr design_angular_to_xml_node(design_angular_s *a);
xmlNodePtr design_angular_root_node(xmlDocPtr doc);
design_angular_s *design_angular_from_xml_doc(xmlDocPtr doc);
design_angular_s *design_angular_from_xml_node(xmlNodePtr node);
design_angular_s *design_angular_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_ANGULAR_XML_H
