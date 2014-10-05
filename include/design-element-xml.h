#ifndef DESIGN_ELEMENT_XML_H
#define DESIGN_ELEMENT_XML_H

#include "design-element.h"

#include "color-xml.h"

#include "design-dimension-xml.h"
#include "design-elliptic-xml.h"
#include "design-line-xml.h"
#include "design-point-xml.h"
#include "design-polyline-xml.h"
#include "design-spline-xml.h"
#include "design-text-xml.h"
#include "design-tolerance-xml.h"

xmlDocPtr design_element_to_xml_doc(design_element_s *e);
xmlNodePtr design_element_to_xml_node(design_element_s *e);
xmlNodePtr design_element_root_node(xmlDocPtr doc);
design_element_s *design_element_from_xml_doc(xmlDocPtr doc);
design_element_s *design_element_from_xml_node(xmlNodePtr node);
design_element_s *design_element_sieve(FILE *infile, FILE *outfile);

#endif // DESIGN_ELEMENT_XML_H
