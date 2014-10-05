#ifndef TITLE_BLOCK_XML_H
#define TITLE_BLOCK_XML_H

#include "title-block.h"

#include "color-xml.h"

xmlDocPtr title_block_to_xml_doc(title_block_s *tb);
xmlNodePtr title_block_to_xml_node(title_block_s *tb);
xmlNodePtr title_block_root_node(xmlDocPtr doc);
title_block_s *title_block_from_xml_doc(xmlDocPtr node);
title_block_s *title_block_from_xml_node(xmlNodePtr node);
title_block_s *title_block_sieve(FILE *infile, FILE *outfile);

#endif // TITLE_BLOCK_XML_H
