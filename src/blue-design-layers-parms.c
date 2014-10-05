#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "units.h"
#include "design-layer-xml.h"

#include "blue-design-layers-parms.h"

static unsigned char errors[blue_design_layers_parameter_END
                            - blue_design_layers_parameter_BEG];
static unsigned char changed[blue_design_layers_parameter_END
                             - blue_design_layers_parameter_BEG];

static unsigned char get_error(blue_design_layers_parameter_t p);
static void set_error(blue_design_layers_parameter_t p);
static void unset_errors(void);

design_layers_s *blue_design_layers_parameter_handler(int argc,
                                                      char** argv,
                                                      design_layers_s *ls)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "layer-xml", 1, 0, blue_design_layers_parameter_layer_xml },
      { 0, 0, 0, 0 }
    };
  design_layer_s *l;
  xmlDocPtr doc;

  if (!ls) ls = design_layers_create();
  if (!ls) return NULL;

  blue_design_layers_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_layers_parameter_layer_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        l = design_layer_from_xml_doc(doc);
        if (l)
          design_layers_add_layer(ls, l);
        xmlFreeDoc(doc);
        blue_design_layers_set_change(blue_design_layers_parameter_layer_xml);
        break;
      default: break;
    }
  }

  blue_design_layers_unset_changes();

  return ls;
}

int blue_design_layers_check(design_layers_s *ls)
{
  int i;

  assert(ls);

  unset_errors();

  for (i = blue_design_layers_parameter_BEG;
       i < blue_design_layers_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_layers_check_error(void)
{
}

unsigned char blue_design_layers_get_change(blue_design_layers_parameter_t p)
{
  return changed[p - blue_design_layers_parameter_BEG];
}

void blue_design_layers_set_change(blue_design_layers_parameter_t p)
{
  changed[p - blue_design_layers_parameter_BEG] = 1;
}

void blue_design_layers_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_layers_parameter_t p)
{
  return errors[p - blue_design_layers_parameter_BEG];
}

static void set_error(blue_design_layers_parameter_t p)
{
  errors[p - blue_design_layers_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

