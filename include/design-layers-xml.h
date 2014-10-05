#ifndef DESIGN_LAYERS_XML_H
#define DESIGN_LAYERS_XML_H

#include "design-layers.h"

#include "design-layer-xml.h"

xmlDocPtr design_layers_to_xml_doc(design_layers_s *ls);
xmlNodePtr design_layers_to_xml_node(design_layers_s *ls);
xmlNodePtr design_layers_root_node(xmlDocPtr doc);
design_layers_s *design_layers_from_xml_doc(xmlDocPtr doc);
design_layers_s *design_layers_from_xml_node(xmlNodePtr node);
design_layers_s *design_layers_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_LAYERS_XML_H
