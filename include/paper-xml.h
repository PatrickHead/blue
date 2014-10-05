#ifndef PAPER_XML_H
#define PAPER_XML_H

#include "paper.h"

#include "color-xml.h"

#include "margins-xml.h"

xmlDocPtr paper_to_xml_doc(paper_s *p);
xmlNodePtr paper_to_xml_node(paper_s *p);
xmlNodePtr paper_root_node(xmlDocPtr doc);
paper_s *paper_from_xml_doc(xmlDocPtr doc);
paper_s *paper_from_xml_node(xmlNodePtr node);
paper_s *paper_sieve(FILE *infile, FILE *outfile);

#endif // PAPER_XML_H
