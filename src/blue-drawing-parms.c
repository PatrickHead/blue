#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "units.h"
#include "paper-xml.h"
#include "border-xml.h"
#include "title-block-xml.h"
#include "design-xml.h"

#include "blue-drawing-parms.h"

static unsigned char errors[blue_drawing_parameter_END
                            - blue_drawing_parameter_BEG];
static unsigned char changed[blue_drawing_parameter_END
                             - blue_drawing_parameter_BEG];

static unsigned char get_error(blue_drawing_parameter_t p);
static void set_error(blue_drawing_parameter_t p);
static void unset_errors(void);

drawing_s *blue_drawing_parameter_handler(int argc, char** argv, drawing_s *d)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "paper-xml", 1, 0, blue_drawing_parameter_paper_xml },
      { "border-xml", 1, 0, blue_drawing_parameter_border_xml },
      { "title-block-xml", 1, 0, blue_drawing_parameter_title_block_xml },
      { "design-xml", 1, 0, blue_drawing_parameter_design_xml },
      { 0, 0, 0, 0 }
    };
  paper_s *paper;
  border_s *border;
  title_block_s *title_block;
  design_s *design;
  xmlDocPtr doc;

  if (!d) d = drawing_create();
  if (!d) return NULL;

  blue_drawing_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_drawing_parameter_paper_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        paper = paper_from_xml_doc(doc);
        if (paper)
          drawing_set_paper(d, paper);
        xmlFreeDoc(doc);
        blue_drawing_set_change(blue_drawing_parameter_paper_xml);
        break;
      case blue_drawing_parameter_border_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        border = border_from_xml_doc(doc);
        if (border)
          drawing_set_border(d, border);
        xmlFreeDoc(doc);
        blue_drawing_set_change(blue_drawing_parameter_border_xml);
        break;
      case blue_drawing_parameter_title_block_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        title_block = title_block_from_xml_doc(doc);
        if (title_block)
          drawing_set_title_block(d, title_block);
        xmlFreeDoc(doc);
        blue_drawing_set_change(blue_drawing_parameter_title_block_xml);
        break;
      case blue_drawing_parameter_design_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        design = design_from_xml_doc(doc);
        if (design)
          drawing_set_design(d, design);
        xmlFreeDoc(doc);
        blue_drawing_set_change(blue_drawing_parameter_design_xml);
        break;
      default: break;
    }
  }

  blue_drawing_unset_changes();

  return d;
}

int blue_drawing_check(drawing_s *d)
{
  int i;

  assert(d);

  unset_errors();

  for (i = blue_drawing_parameter_BEG;
       i < blue_drawing_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_drawing_check_error(void)
{
  if (get_error(blue_drawing_parameter_paper_xml))
    fprintf(stderr, "Parameter Error; paper-xml\n");
  if (get_error(blue_drawing_parameter_border_xml))
    fprintf(stderr, "Parameter Error; border-xml\n");
  if (get_error(blue_drawing_parameter_title_block_xml))
    fprintf(stderr, "Parameter Error; title-block-xml\n");
  if (get_error(blue_drawing_parameter_design_xml))
    fprintf(stderr, "Parameter Error; design-xml\n");
}

unsigned char blue_drawing_get_change(blue_drawing_parameter_t p)
{
  return changed[p - blue_drawing_parameter_BEG];
}

void blue_drawing_set_change(blue_drawing_parameter_t p)
{
  changed[p - blue_drawing_parameter_BEG] = 1;
}

void blue_drawing_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_drawing_parameter_t p)
{
  return errors[p - blue_drawing_parameter_BEG];
}

static void set_error(blue_drawing_parameter_t p)
{
  errors[p - blue_drawing_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

