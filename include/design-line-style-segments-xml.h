#ifndef DESIGN_LINE_STYLE_SEGMENTS_XML_H
#define DESIGN_LINE_STYLE_SEGMENTS_XML_H

#include "design-line-style-segments.h"

#include "design-line-style-segment-xml.h"

xmlDocPtr design_line_style_segments_to_xml_doc(
  design_line_style_segments_s *lsss);
xmlNodePtr design_line_style_segments_to_xml_node(
  design_line_style_segments_s *lsss);
xmlNodePtr design_line_style_segments_root_node(xmlDocPtr doc);
design_line_style_segments_s *design_line_style_segments_from_xml_doc(
  xmlDocPtr doc);
design_line_style_segments_s *design_line_style_segments_from_xml_node(
  xmlNodePtr node);
design_line_style_segments_s *design_line_style_segments_sieve(FILE *infile,
                                                               FILE *outfile);

#endif // DESIGN_LINE_STYLE_SEGMENTS_XML_H
