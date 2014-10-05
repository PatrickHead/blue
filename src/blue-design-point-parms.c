#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "design-defaults-xml.h"

#include "blue-design-point-parms.h"

static unsigned char errors[blue_design_point_parameter_END
                            - blue_design_point_parameter_BEG];
static unsigned char changed[blue_design_point_parameter_END
                             - blue_design_point_parameter_BEG];

static unsigned char get_error(blue_design_point_parameter_t p);
static void set_error(blue_design_point_parameter_t p);
static void unset_errors(void);

design_point_s *blue_design_point_parameter_handler(int argc,
                                                    char** argv,
                                                    design_point_s *p)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "location", 1, 0, blue_design_point_parameter_location },
      { "defaults-xml", 1, 0, blue_design_point_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!p) p = design_point_create();
  if (!p) return NULL;

  blue_design_point_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_point_parameter_location:
        design_point_set_location(p, str2vertex(optarg));
        blue_design_point_set_change(blue_design_point_parameter_location);
        break;
      case blue_design_point_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_point_set_change(blue_design_point_parameter_defaults_xml);
        break;
    }
  }

  blue_design_point_unset_changes();

  return p;
}

int blue_design_point_check(design_point_s *p)
{
  int i;

  assert(p);

  unset_errors();

  for (i = blue_design_point_parameter_BEG;
       i < blue_design_point_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_point_check_error(void)
{
  if (get_error(blue_design_point_parameter_location))
    fprintf(stderr, "Parameter Error; location\n");
  if (get_error(blue_design_point_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_point_get_change(blue_design_point_parameter_t p)
{
  return changed[p - blue_design_point_parameter_BEG];
}

void blue_design_point_set_change(blue_design_point_parameter_t p)
{
  changed[p - blue_design_point_parameter_BEG] = 1;
}

void blue_design_point_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_point_parameter_t p)
{
  return errors[p - blue_design_point_parameter_BEG];
}

static void set_error(blue_design_point_parameter_t p)
{
  errors[p - blue_design_point_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

