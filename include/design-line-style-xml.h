#ifndef DESIGN_LINE_STYLE_XML_H
#define DESIGN_LINE_STYLE_XML_H

#include "design-line-style.h"

xmlDocPtr design_line_style_to_xml_doc(design_line_style_s *ls);
xmlNodePtr design_line_style_to_xml_node(design_line_style_s *ls);
xmlNodePtr design_line_style_root_node(xmlDocPtr doc);
design_line_style_s *design_line_style_from_xml_doc(xmlDocPtr doc);
design_line_style_s *design_line_style_from_xml_node(xmlNodePtr node);
design_line_style_s *design_line_style_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_LINE_STYLE_XML_H
