#ifndef DESIGN_ELLIPTIC_XML_H
#define DESIGN_ELLIPTIC_XML_H

#include "vertex-xml.h"

#include "design-elliptic.h"

xmlDocPtr design_elliptic_to_xml_doc(design_elliptic_s *e);
xmlNodePtr design_elliptic_to_xml_node(design_elliptic_s *e);
xmlNodePtr design_elliptic_root_node(xmlDocPtr doc);
design_elliptic_s *design_elliptic_from_xml_doc(xmlDocPtr doc);
design_elliptic_s *design_elliptic_from_xml_node(xmlNodePtr node);
design_elliptic_s *design_elliptic_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_ELLIPTIC_XML_H
