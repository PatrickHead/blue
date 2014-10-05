#ifndef DESIGN_LINE_STYLES_XML_H
#define DESIGN_LINE_STYLES_XML_H

#include "design-line-styles.h"

#include "design-line-style-xml.h"

xmlDocPtr design_line_styles_to_xml_doc(design_line_styles_s *lss);
xmlNodePtr design_line_styles_to_xml_node(design_line_styles_s *lss);
xmlNodePtr design_line_styles_root_node(xmlDocPtr doc);
design_line_styles_s *design_line_styles_from_xml_doc(xmlDocPtr doc);
design_line_styles_s *design_line_styles_from_xml_node(xmlNodePtr node);
design_line_styles_s *design_line_styles_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_LINE_STYLES_XML_H
