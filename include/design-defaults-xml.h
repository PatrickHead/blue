#ifndef DESIGN_DEFAULTS_XML_H
#define DESIGN_DEFAULTS_XML_H

#include "design-defaults.h"

#include "color-xml.h"

xmlDocPtr design_defaults_to_xml_doc(design_defaults_s *ds);
xmlNodePtr design_defaults_to_xml_node(design_defaults_s *ds);
xmlNodePtr design_defaults_root_node(xmlDocPtr doc);
design_defaults_s *design_defaults_from_xml_doc(xmlDocPtr doc);
design_defaults_s *design_defaults_from_xml_node(xmlNodePtr node);
design_defaults_s *design_defaults_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_DEFAULTS_XML_H
