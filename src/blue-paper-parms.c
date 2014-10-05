#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "margins-xml.h"
#include "color-xml.h"

#include "blue-paper-parms.h"

static unsigned char errors[blue_paper_parameter_END - blue_paper_parameter_BEG];
static unsigned char changed[blue_paper_parameter_END - blue_paper_parameter_BEG];

static unsigned char get_error(blue_paper_parameter_t p);
static void set_error(blue_paper_parameter_t p);
static void unset_errors(void);

paper_s *blue_paper_parameter_handler(int argc, char** argv, paper_s *p)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "units", 1, 0, blue_paper_parameter_units },
      { "size", 1, 0, blue_paper_parameter_size },
      { "orientation", 1, 0, blue_paper_parameter_orientation },
      { "margins-xml", 1, 0, blue_paper_parameter_margins_xml },
      { "width", 1, 0, blue_paper_parameter_width },
      { "height", 1, 0, blue_paper_parameter_height },
      { "color-xml", 1, 0, blue_paper_parameter_color_xml },
      { 0, 0, 0, 0 }
    };
  xmlDocPtr doc;
  margins_s *m;
  color_s *color;

  if (!p) p = paper_create();
  if (!p) return NULL;

  blue_paper_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_paper_parameter_units:
        paper_set_units(p, str2units(optarg));
        blue_paper_set_change(blue_paper_parameter_units);
        break;
      case blue_paper_parameter_size:
        paper_set_size(p, str2paper_size(optarg));
        blue_paper_set_change(blue_paper_parameter_size);
        break;
      case blue_paper_parameter_orientation:
        paper_set_orientation(p, str2paper_orientation(optarg));
        blue_paper_set_change(blue_paper_parameter_orientation);
        break;
      case blue_paper_parameter_margins_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        m = margins_from_xml_doc(doc);
        if (m)
          paper_set_margins(p, m);
        blue_paper_set_change(blue_paper_parameter_margins_xml);
        xmlFreeDoc(doc);
        break;
      case blue_paper_parameter_width:
        paper_set_width(p, strtod(optarg, NULL));
        blue_paper_set_change(blue_paper_parameter_width);
        break;
      case blue_paper_parameter_height:
        paper_set_height(p, strtod(optarg, NULL));
        blue_paper_set_change(blue_paper_parameter_height);
        break;
      case blue_paper_parameter_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          paper_set_color(p, color);
        blue_paper_set_change(blue_paper_parameter_color_xml);
        xmlFreeDoc(doc);
        break;
    }
  }

  blue_paper_unset_changes();

  return p;
}

int blue_paper_check(paper_s *p)
{
  int i;

  assert(p);

  unset_errors();

  if (p->width <= 0.0) set_error(blue_paper_parameter_width);
  if (p->height <= 0.0) set_error(blue_paper_parameter_height);

  for (i = blue_paper_parameter_BEG; i < blue_paper_parameter_END; i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_paper_check_error(void)
{
  if (get_error(blue_paper_parameter_units))
    fprintf(stderr, "Parameter Error; units\n");
  if (get_error(blue_paper_parameter_size))
    fprintf(stderr, "Parameter Error; size\n");
  if (get_error(blue_paper_parameter_orientation))
    fprintf(stderr, "Parameter Error; orientation\n");
  if (get_error(blue_paper_parameter_margins_xml))
    fprintf(stderr, "Parameter Error; margins-xml\n");
  if (get_error(blue_paper_parameter_width))
    fprintf(stderr, "Parameter Error; width\n");
  if (get_error(blue_paper_parameter_height))
    fprintf(stderr, "Parameter Error; height\n");
  if (get_error(blue_paper_parameter_color_xml))
    fprintf(stderr, "Parameter Error; color-xml\n");
}

unsigned char blue_paper_get_change(blue_paper_parameter_t p)
{
  return changed[p - blue_paper_parameter_BEG];
}

void blue_paper_set_change(blue_paper_parameter_t p)
{
  changed[p - blue_paper_parameter_BEG] = 1;
}

void blue_paper_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_paper_parameter_t p)
{
  return errors[p - blue_paper_parameter_BEG];
}

static void set_error(blue_paper_parameter_t p)
{
  errors[p - blue_paper_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

