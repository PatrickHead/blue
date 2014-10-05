#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "units.h"

#include "design-defaults-xml.h"

#include "blue-design-angular-parms.h"

static unsigned char errors[blue_design_angular_parameter_END - blue_design_angular_parameter_BEG];
static unsigned char changed[blue_design_angular_parameter_END - blue_design_angular_parameter_BEG];

static unsigned char get_error(blue_design_angular_parameter_t p);
static void set_error(blue_design_angular_parameter_t p);
static void unset_errors(void);

design_angular_s *blue_design_angular_parameter_handler(int argc,
                                                        char** argv,
                                                        design_angular_s *a)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "angle", 1, 0, blue_design_angular_parameter_angle },
      { "alpha", 1, 0, blue_design_angular_parameter_alpha },
      { "beta", 1, 0, blue_design_angular_parameter_beta },
      { "gamma", 1, 0, blue_design_angular_parameter_gamma },
      { "gap", 1, 0, blue_design_angular_parameter_gap },
      { "extension", 1, 0, blue_design_angular_parameter_extension },
      { "defaults-xml", 1, 0, blue_design_angular_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!a) a = design_angular_create();
  if (!a) return NULL;

  blue_design_angular_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_angular_parameter_angle:
        design_angular_set_angle(a, strtod(optarg, NULL));
        blue_design_angular_set_change(blue_design_angular_parameter_angle);
        break;
      case blue_design_angular_parameter_alpha:
        design_angular_set_alpha(a, str2vertex(optarg));
        blue_design_angular_set_change(blue_design_angular_parameter_alpha);
        break;
      case blue_design_angular_parameter_beta:
        design_angular_set_beta(a, str2vertex(optarg));
        blue_design_angular_set_change(blue_design_angular_parameter_beta);
        break;
      case blue_design_angular_parameter_gamma:
        design_angular_set_gamma(a, str2vertex(optarg));
        blue_design_angular_set_change(blue_design_angular_parameter_gamma);
        break;
      case blue_design_angular_parameter_gap:
        design_angular_set_gap(a, strtod(optarg, NULL));
        blue_design_angular_set_change(blue_design_angular_parameter_gap);
        break;
      case blue_design_angular_parameter_extension:
        design_angular_set_extension(a, strtod(optarg, NULL));
        blue_design_angular_set_change(blue_design_angular_parameter_extension);
        break;
      case blue_design_angular_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d)
          design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_angular_set_change(
          blue_design_angular_parameter_defaults_xml);
        break;
    }
  }

  blue_design_angular_unset_changes();

  return a;
}

int blue_design_angular_check(design_angular_s *a)
{
  int i;

  assert(a);

  unset_errors();

  if (a->angle < 0.0) set_error(blue_design_angular_parameter_angle);
  if (a->gap < 0.0) set_error(blue_design_angular_parameter_gap);
  if (a->extension < 0.0) set_error(blue_design_angular_parameter_extension);

  for (i = blue_design_angular_parameter_BEG;
       i < blue_design_angular_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_angular_check_error(void)
{
  if (get_error(blue_design_angular_parameter_angle))
    fprintf(stderr, "Parameter Error; angle\n");
  if (get_error(blue_design_angular_parameter_alpha))
    fprintf(stderr, "Parameter Error; alpha\n");
  if (get_error(blue_design_angular_parameter_beta))
    fprintf(stderr, "Parameter Error; beta\n");
  if (get_error(blue_design_angular_parameter_gamma))
    fprintf(stderr, "Parameter Error; gamma\n");
  if (get_error(blue_design_angular_parameter_gap))
    fprintf(stderr, "Parameter Error; gap\n");
  if (get_error(blue_design_angular_parameter_extension))
    fprintf(stderr, "Parameter Error; extension\n");
  if (get_error(blue_design_angular_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_angular_get_change(blue_design_angular_parameter_t p)
{
  return changed[p - blue_design_angular_parameter_BEG];
}

void blue_design_angular_set_change(blue_design_angular_parameter_t p)
{
  changed[p - blue_design_angular_parameter_BEG] = 1;
}

void blue_design_angular_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_angular_parameter_t p)
{
  return errors[p - blue_design_angular_parameter_BEG];
}

static void set_error(blue_design_angular_parameter_t p)
{
  errors[p - blue_design_angular_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

