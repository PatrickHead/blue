#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "design-defaults-xml.h"
#include "design-line-styles-xml.h"
#include "design-fill-styles-xml.h"
#include "design-layers-xml.h"

#include "blue-design-parms.h"

static unsigned char errors[blue_design_parameter_END
                            - blue_design_parameter_BEG];
static unsigned char changed[blue_design_parameter_END
                             - blue_design_parameter_BEG];

static unsigned char get_error(blue_design_parameter_t p);
static void set_error(blue_design_parameter_t p);
static void unset_errors(void);

design_s *blue_design_parameter_handler(int argc, char** argv, design_s *d)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "defaults-xml", 1, 0, blue_design_parameter_defaults_xml },
      { "line-styles-xml", 1, 0, blue_design_parameter_line_styles_xml },
      { "fill-styles-xml", 1, 0, blue_design_parameter_fill_styles_xml },
      { "layers-xml", 1, 0, blue_design_parameter_layers_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *defaults;
  design_line_styles_s *line_styles;
  design_fill_styles_s *fill_styles;
  design_layers_s *layers;
  xmlDocPtr doc;

  if (!d) d = design_create();
  if (!d) return NULL;

  blue_design_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        defaults = design_defaults_from_xml_doc(doc);
        if (defaults)
          design_set_defaults(d, defaults);
        xmlFreeDoc(doc);
        blue_design_set_change(
          blue_design_parameter_defaults_xml);
        break;
      case blue_design_parameter_line_styles_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        line_styles = design_line_styles_from_xml_doc(doc);
        if (line_styles)
          design_set_line_styles(d, line_styles);
        xmlFreeDoc(doc);
        blue_design_set_change(
          blue_design_parameter_line_styles_xml);
        break;
      case blue_design_parameter_fill_styles_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        fill_styles = design_fill_styles_from_xml_doc(doc);
        if (fill_styles)
          design_set_fill_styles(d, fill_styles);
        xmlFreeDoc(doc);
        blue_design_set_change(
          blue_design_parameter_fill_styles_xml);
        break;
      case blue_design_parameter_layers_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        layers = design_layers_from_xml_doc(doc);
        if (layers)
          design_set_layers(d, layers);
        xmlFreeDoc(doc);
        blue_design_set_change(
          blue_design_parameter_layers_xml);
        break;
      default: break;
    }
  }

  blue_design_unset_changes();

  return d;
}

int blue_design_check(design_s *d)
{
  int i;

  assert(d);

  unset_errors();

  for (i = blue_design_parameter_BEG;
       i < blue_design_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_check_error(void)
{
  if (get_error(blue_design_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
  if (get_error(blue_design_parameter_line_styles_xml))
    fprintf(stderr, "Parameter Error; line-styles-xml\n");
  if (get_error(blue_design_parameter_fill_styles_xml))
    fprintf(stderr, "Parameter Error; fill-styles-xml\n");
  if (get_error(blue_design_parameter_layers_xml))
    fprintf(stderr, "Parameter Error; layers-xml\n");
}

unsigned char blue_design_get_change(blue_design_parameter_t p)
{
  return changed[p - blue_design_parameter_BEG];
}

void blue_design_set_change(blue_design_parameter_t p)
{
  changed[p - blue_design_parameter_BEG] = 1;
}

void blue_design_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_parameter_t p)
{
  return errors[p - blue_design_parameter_BEG];
}

static void set_error(blue_design_parameter_t p)
{
  errors[p - blue_design_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

