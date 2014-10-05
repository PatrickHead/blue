#ifndef DRAWING_XML_H
#define DRAWING_XML_H

#include "drawing.h"

xmlDocPtr drawing_to_xml_doc(drawing_s *d);
xmlNodePtr drawing_to_xml_node(drawing_s *d);
xmlNodePtr drawing_root_node(xmlDocPtr doc);
drawing_s *drawing_from_xml_doc(xmlDocPtr doc);
drawing_s *drawing_from_xml_node(xmlNodePtr node);
drawing_s *drawing_sieve(FILE *infile, FILE *outfile);

#endif // DRAWING_XML_H
