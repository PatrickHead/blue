#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "units.h"
#include "design-element-xml.h"

#include "blue-design-elements-parms.h"

static unsigned char errors[blue_design_elements_parameter_END
                            - blue_design_elements_parameter_BEG];
static unsigned char changed[blue_design_elements_parameter_END
                             - blue_design_elements_parameter_BEG];

static unsigned char get_error(blue_design_elements_parameter_t p);
static void set_error(blue_design_elements_parameter_t p);
static void unset_errors(void);

design_elements_s *blue_design_elements_parameter_handler(int argc,
                                                          char** argv,
                                                          design_elements_s *es)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "element-xml", 1, 0, blue_design_elements_parameter_element_xml },
      { 0, 0, 0, 0 }
    };
  design_element_s *e;
  xmlDocPtr doc;

  if (!es) es = design_elements_create();
  if (!es) return NULL;

  blue_design_elements_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_elements_parameter_element_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        e = design_element_from_xml_doc(doc);
        if (e)
          design_elements_add_element(es, e);
        xmlFreeDoc(doc);
        blue_design_elements_set_change(
           blue_design_elements_parameter_element_xml);
        break;
      default: break;
    }
  }

  blue_design_elements_unset_changes();

  return es;
}

int blue_design_elements_check(design_elements_s *es)
{
  int i;

  assert(es);

  unset_errors();

  for (i = blue_design_elements_parameter_BEG;
       i < blue_design_elements_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_elements_check_error(void)
{
}

unsigned char blue_design_elements_get_change(blue_design_elements_parameter_t p)
{
  return changed[p - blue_design_elements_parameter_BEG];
}

void blue_design_elements_set_change(blue_design_elements_parameter_t p)
{
  changed[p - blue_design_elements_parameter_BEG] = 1;
}

void blue_design_elements_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_elements_parameter_t p)
{
  return errors[p - blue_design_elements_parameter_BEG];
}

static void set_error(blue_design_elements_parameter_t p)
{
  errors[p - blue_design_elements_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

