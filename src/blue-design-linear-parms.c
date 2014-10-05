#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "units.h"

#include "design-defaults-xml.h"

#include "blue-design-linear-parms.h"

static unsigned char errors[blue_design_linear_parameter_END - blue_design_linear_parameter_BEG];
static unsigned char changed[blue_design_linear_parameter_END - blue_design_linear_parameter_BEG];

static unsigned char get_error(blue_design_linear_parameter_t p);
static void set_error(blue_design_linear_parameter_t p);
static void unset_errors(void);

design_linear_s *blue_design_linear_parameter_handler(int argc,
                                                      char** argv,
                                                      design_linear_s *l)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "start", 1, 0, blue_design_linear_parameter_start },
      { "end", 1, 0, blue_design_linear_parameter_end },
      { "gap", 1, 0, blue_design_linear_parameter_gap },
      { "extension-above", 1, 0, blue_design_linear_parameter_extension_above },
      { "extension-below", 1, 0, blue_design_linear_parameter_extension_below },
      { "dimension", 1, 0, blue_design_linear_parameter_dimension },
      { "defaults-xml", 1, 0, blue_design_linear_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!l) l = design_linear_create();
  if (!l) return NULL;

  blue_design_linear_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_linear_parameter_start:
        design_linear_set_start(l, str2vertex(optarg));
        blue_design_linear_set_change(blue_design_linear_parameter_start);
        break;
      case blue_design_linear_parameter_end:
        design_linear_set_end(l, str2vertex(optarg));
        blue_design_linear_set_change(blue_design_linear_parameter_end);
        break;
      case blue_design_linear_parameter_gap:
        design_linear_set_gap(l, strtod(optarg, NULL));
        blue_design_linear_set_change(blue_design_linear_parameter_gap);
        break;
      case blue_design_linear_parameter_extension_above:
        design_linear_set_extension_above(l, strtod(optarg, NULL));
        blue_design_linear_set_change(
          blue_design_linear_parameter_extension_above);
        break;
      case blue_design_linear_parameter_extension_below:
        design_linear_set_extension_below(l, strtod(optarg, NULL));
        blue_design_linear_set_change(
          blue_design_linear_parameter_extension_below);
        break;
      case blue_design_linear_parameter_dimension:
        design_linear_set_dimension(l, strtod(optarg, NULL));
        blue_design_linear_set_change(blue_design_linear_parameter_dimension);
        break;
      case blue_design_linear_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_linear_set_change(blue_design_linear_parameter_defaults_xml);
        break;
    }
  }

  blue_design_linear_unset_changes();

  return l;
}

int blue_design_linear_check(design_linear_s *l)
{
  int i;

  assert(l);

  unset_errors();

  if (l->gap < 0.0) set_error(blue_design_linear_parameter_gap);
  if (l->extension_above < 0.0)
    set_error(blue_design_linear_parameter_extension_above);
  if (l->extension_below < 0.0)
    set_error(blue_design_linear_parameter_extension_below);
  if (l->dimension < 0.0) set_error(blue_design_linear_parameter_dimension);

  for (i = blue_design_linear_parameter_BEG;
       i < blue_design_linear_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_linear_check_error(void)
{
  if (get_error(blue_design_linear_parameter_start))
    fprintf(stderr, "Parameter Error; start\n");
  if (get_error(blue_design_linear_parameter_end))
    fprintf(stderr, "Parameter Error; end\n");
  if (get_error(blue_design_linear_parameter_gap))
    fprintf(stderr, "Parameter Error; gap\n");
  if (get_error(blue_design_linear_parameter_extension_above))
    fprintf(stderr, "Parameter Error; extension_above\n");
  if (get_error(blue_design_linear_parameter_extension_below))
    fprintf(stderr, "Parameter Error; extension_below\n");
  if (get_error(blue_design_linear_parameter_dimension))
    fprintf(stderr, "Parameter Error; dimension\n");
  if (get_error(blue_design_linear_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_linear_get_change(blue_design_linear_parameter_t p)
{
  return changed[p - blue_design_linear_parameter_BEG];
}

void blue_design_linear_set_change(blue_design_linear_parameter_t p)
{
  changed[p - blue_design_linear_parameter_BEG] = 1;
}

void blue_design_linear_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_linear_parameter_t p)
{
  return errors[p - blue_design_linear_parameter_BEG];
}

static void set_error(blue_design_linear_parameter_t p)
{
  errors[p - blue_design_linear_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

