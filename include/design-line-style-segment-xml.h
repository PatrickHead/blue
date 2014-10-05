#ifndef DESIGN_LINE_STYLE_SEGMENT_XML_H
#define DESIGN_LINE_STYLE_SEGMENT_XML_H

#include "vertex-xml.h"

#include "design-line-style-segment.h"

xmlDocPtr design_line_style_segment_to_xml_doc(
  design_line_style_segment_s *lss);
xmlNodePtr design_line_style_segment_to_xml_node(
  design_line_style_segment_s *lss);
xmlNodePtr design_line_style_segment_root_node(xmlDocPtr doc);
design_line_style_segment_s *design_line_style_segment_from_xml_doc(
  xmlDocPtr doc);
design_line_style_segment_s *design_line_style_segment_from_xml_node(
  xmlNodePtr node);
design_line_style_segment_s *design_line_style_segment_sieve(FILE *infile,
                                                             FILE *outfile);

#endif // DESIGN_LINE_STYLE_SEGMENT_XML_H
