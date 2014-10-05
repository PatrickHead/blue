#ifndef DESIGN_LAYER_XML_H
#define DESIGN_LAYER_XML_H

#include "design-layer.h"

#include "design-defaults-xml.h"
#include "design-elements-xml.h"

xmlDocPtr design_layer_to_xml_doc(design_layer_s *l);
xmlNodePtr design_layer_to_xml_node(design_layer_s *l);
xmlNodePtr design_layer_root_node(xmlDocPtr doc);
design_layer_s *design_layer_from_xml_doc(xmlDocPtr doc);
design_layer_s *design_layer_from_xml_node(xmlNodePtr node);
design_layer_s *design_layer_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_LAYER_XML_H
