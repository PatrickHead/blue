#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "units.h"

#include "design-defaults-xml.h"

#include "blue-design-fill-parms.h"

static unsigned char errors[blue_design_fill_parameter_END
                            - blue_design_fill_parameter_BEG];
static unsigned char changed[blue_design_fill_parameter_END
                             - blue_design_fill_parameter_BEG];

static unsigned char get_error(blue_design_fill_parameter_type p);
static void set_error(blue_design_fill_parameter_type p);
static void unset_errors(void);

design_fill_s *blue_design_fill_parameter_handler(int argc,
                                                  char** argv,
                                                  design_fill_s *f)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "defaults-xml", 1, 0, blue_design_fill_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!f) f = design_fill_create();
  if (!f) return NULL;

  blue_design_fill_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_fill_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_fill_set_change(blue_design_fill_parameter_defaults_xml);
        break;
      default: break;
    }
  }

  blue_design_fill_unset_changes();

  return f;
}

int blue_design_fill_check(design_fill_s *f)
{
  int i;

  assert(f);

  unset_errors();

  for (i = blue_design_fill_parameter_BEG;
       i < blue_design_fill_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_fill_check_error(void)
{
  if (get_error(blue_design_fill_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_fill_get_change(blue_design_fill_parameter_type p)
{
  return changed[p - blue_design_fill_parameter_BEG];
}

void blue_design_fill_set_change(blue_design_fill_parameter_type p)
{
  changed[p - blue_design_fill_parameter_BEG] = 1;
}

void blue_design_fill_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_fill_parameter_type p)
{
  return errors[p - blue_design_fill_parameter_BEG];
}

static void set_error(blue_design_fill_parameter_type p)
{
  errors[p - blue_design_fill_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

