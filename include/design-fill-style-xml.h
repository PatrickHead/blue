#ifndef DESIGN_FILL_STYLE_XML_H
#define DESIGN_FILL_STYLE_XML_H

#include "color-xml.h"

#include "design-fill-style.h"

xmlDocPtr design_fill_style_to_xml_doc(design_fill_style_s *fs);
xmlNodePtr design_fill_style_to_xml_node(design_fill_style_s *fs);
xmlNodePtr design_fill_style_root_node(xmlDocPtr doc);
design_fill_style_s *design_fill_style_from_xml_doc(xmlDocPtr doc);
design_fill_style_s *design_fill_style_from_xml_node(xmlNodePtr node);
design_fill_style_s *design_fill_style_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_FILL_STYLE_XML_H
