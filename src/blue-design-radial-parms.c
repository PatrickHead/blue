#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "units.h"

#include "design-defaults-xml.h"

#include "blue-design-radial-parms.h"

static unsigned char errors[blue_design_radial_parameter_END - blue_design_radial_parameter_BEG];
static unsigned char changed[blue_design_radial_parameter_END - blue_design_radial_parameter_BEG];

static unsigned char get_error(blue_design_radial_parameter_t p);
static void set_error(blue_design_radial_parameter_t p);
static void unset_errors(void);

design_radial_s *blue_design_radial_parameter_handler(int argc,
                                                      char** argv,
                                                      design_radial_s *r)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "type", 1, 0, blue_design_radial_parameter__type },
      { "center", 1, 0, blue_design_radial_parameter_center },
      { "major", 1, 0, blue_design_radial_parameter_major },
      { "minor", 1, 0, blue_design_radial_parameter_minor },
      { "angle", 1, 0, blue_design_radial_parameter_angle },
      { "leader", 1, 0, blue_design_radial_parameter_leader },
      { "defaults-xml", 1, 0, blue_design_radial_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!r) r = design_radial_create();
  if (!r) return NULL;

  blue_design_radial_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_radial_parameter__type:
        design_radial_set_type(r, str2design_radial_type(optarg));
        blue_design_radial_set_change(blue_design_radial_parameter_angle);
        break;
      case blue_design_radial_parameter_center:
        design_radial_set_center(r, str2vertex(optarg));
        blue_design_radial_set_change(blue_design_radial_parameter_center);
        break;
      case blue_design_radial_parameter_major:
        design_radial_set_major(r, strtod(optarg, NULL));
        blue_design_radial_set_change(blue_design_radial_parameter_major);
        break;
      case blue_design_radial_parameter_minor:
        design_radial_set_minor(r, strtod(optarg, NULL));
        blue_design_radial_set_change(blue_design_radial_parameter_minor);
        break;
      case blue_design_radial_parameter_angle:
        design_radial_set_angle(r, strtod(optarg, NULL));
        blue_design_radial_set_change(blue_design_radial_parameter_angle);
        break;
      case blue_design_radial_parameter_leader:
        design_radial_set_leader(r, strtod(optarg, NULL));
        blue_design_radial_set_change(blue_design_radial_parameter_leader);
        break;
      case blue_design_radial_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_radial_set_change(blue_design_radial_parameter_defaults_xml);
        break;
    }
  }

  blue_design_radial_unset_changes();

  return r;
}

int blue_design_radial_check(design_radial_s *r)
{
  int i;

  assert(r);

  unset_errors();

  if (r->major < 0.0) set_error(blue_design_radial_parameter_major);
  if (r->minor < 0.0) set_error(blue_design_radial_parameter_minor);
  if (r->angle < 0.0) set_error(blue_design_radial_parameter_angle);
  if (r->leader < 0.0) set_error(blue_design_radial_parameter_leader);

  for (i = blue_design_radial_parameter_BEG;
       i < blue_design_radial_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_radial_check_error(void)
{
  if (get_error(blue_design_radial_parameter__type))
    fprintf(stderr, "Parameter Error; type\n");
  if (get_error(blue_design_radial_parameter_center))
    fprintf(stderr, "Parameter Error; center\n");
  if (get_error(blue_design_radial_parameter_major))
    fprintf(stderr, "Parameter Error; major\n");
  if (get_error(blue_design_radial_parameter_minor))
    fprintf(stderr, "Parameter Error; minor\n");
  if (get_error(blue_design_radial_parameter_angle))
    fprintf(stderr, "Parameter Error; angle\n");
  if (get_error(blue_design_radial_parameter_leader))
    fprintf(stderr, "Parameter Error; leader\n");
  if (get_error(blue_design_radial_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_radial_get_change(blue_design_radial_parameter_t p)
{
  return changed[p - blue_design_radial_parameter_BEG];
}

void blue_design_radial_set_change(blue_design_radial_parameter_t p)
{
  changed[p - blue_design_radial_parameter_BEG] = 1;
}

void blue_design_radial_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_radial_parameter_t p)
{
  return errors[p - blue_design_radial_parameter_BEG];
}

static void set_error(blue_design_radial_parameter_t p)
{
  errors[p - blue_design_radial_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

