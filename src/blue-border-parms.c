#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "margins-xml.h"
#include "color-xml.h"

#include "blue-border-parms.h"

static unsigned char errors[blue_border_parameter_END - blue_border_parameter_BEG];
static unsigned char changed[blue_border_parameter_END - blue_border_parameter_BEG];

static unsigned char get_error(blue_border_parameter_t p);
static void set_error(blue_border_parameter_t p);
static void unset_errors(void);

border_s *blue_border_parameter_handler(int argc, char** argv, border_s *b)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "units", 1, 0, blue_border_parameter_units },
      { "line-width", 1, 0, blue_border_parameter_line_width },
      { "background-color-xml",
         1,
         0,
         blue_border_parameter_background_color_xml },
      { "line-color-xml", 1, 0, blue_border_parameter_line_color_xml },
      { "margins-xml", 1, 0, blue_border_parameter_margins_xml },
      { 0, 0, 0, 0 }
    };
  xmlDocPtr doc;
  margins_s *m;
  color_s *color;

  if (!b) b = border_create();
  if (!b) return NULL;

  blue_border_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_border_parameter_units:
        border_set_units(b, str2units(optarg));
        margins_set_units(b->margins, str2units(optarg));
        blue_border_set_change(blue_border_parameter_units);
        break;
      case blue_border_parameter_line_width:
        border_set_line_width(b, strtod(optarg, NULL));
        blue_border_set_change(blue_border_parameter_line_width);
        break;
      case blue_border_parameter_background_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          border_set_background_color(b, color);
        blue_border_set_change(blue_border_parameter_background_color_xml);
        xmlFreeDoc(doc);
        break;
      case blue_border_parameter_line_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          border_set_line_color(b, color);
        blue_border_set_change(blue_border_parameter_line_color_xml);
        xmlFreeDoc(doc);
        break;
      case blue_border_parameter_margins_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        m = margins_from_xml_doc(doc);
        if (m)
          border_set_margins(b, m);
        blue_border_set_change(blue_border_parameter_margins_xml);
        xmlFreeDoc(doc);
        break;
    }
  }

  blue_border_unset_changes();

  return b;
}

int blue_border_check(border_s *b)
{
  int i;

  assert(b);

  unset_errors();

  if (b->line_width < 0.0) set_error(blue_border_parameter_line_width);

  for (i = blue_border_parameter_BEG; i < blue_border_parameter_END; i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_border_check_error(void)
{
  if (get_error(blue_border_parameter_units))
    fprintf(stderr, "Parameter Error; units\n");
  if (get_error(blue_border_parameter_line_width))
    fprintf(stderr, "Parameter Error; line-width\n");
  if (get_error(blue_border_parameter_background_color_xml))
    fprintf(stderr, "Parameter Error; background-color-xml\n");
  if (get_error(blue_border_parameter_line_color_xml))
    fprintf(stderr, "Parameter Error; line-color-xml\n");
  if (get_error(blue_border_parameter_margins_xml))
    fprintf(stderr, "Parameter Error; margins-xml\n");
}

unsigned char blue_border_get_change(blue_border_parameter_t p)
{
  return changed[p - blue_border_parameter_BEG];
}

void blue_border_set_change(blue_border_parameter_t p)
{
  changed[p - blue_border_parameter_BEG] = 1;
}

void blue_border_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_border_parameter_t p)
{
  return errors[p - blue_border_parameter_BEG];
}

static void set_error(blue_border_parameter_t p)
{
  errors[p - blue_border_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

