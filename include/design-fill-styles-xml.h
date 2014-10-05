#ifndef DESIGN_FILL_STYLES_XML_H
#define DESIGN_FILL_STYLES_XML_H

#include "design-fill-styles.h"

#include "design-fill-style-xml.h"

xmlDocPtr design_fill_styles_to_xml_doc(design_fill_styles_s *fss);
xmlNodePtr design_fill_styles_to_xml_node(design_fill_styles_s *fss);
xmlNodePtr design_fill_styles_root_node(xmlDocPtr doc);
design_fill_styles_s *design_fill_styles_from_xml_doc(xmlDocPtr doc);
design_fill_styles_s *design_fill_styles_from_xml_node(xmlNodePtr node);
design_fill_styles_s *design_fill_styles_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_FILL_STYLES_XML_H
