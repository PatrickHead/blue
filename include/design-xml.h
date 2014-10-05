#ifndef DESIGN_XML_H
#define DESIGN_XML_H

#include "design.h"

#include "design-defaults-xml.h"
#include "design-line-styles-xml.h"
#include "design-fill-styles-xml.h"
#include "design-layers-xml.h"

xmlDocPtr design_to_xml_doc(design_s *d);
xmlNodePtr design_to_xml_node(design_s *d);
xmlNodePtr design_root_node(xmlDocPtr doc);
design_s *design_from_xml_doc(xmlDocPtr doc);
design_s *design_from_xml_node(xmlNodePtr node);
design_s *design_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_XML_H
