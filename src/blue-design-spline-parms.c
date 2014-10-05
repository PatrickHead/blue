#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "units.h"

#include "vertices-xml.h"
#include "design-defaults-xml.h"

#include "blue-design-spline-parms.h"

static unsigned char errors[blue_design_spline_parameter_END
                            - blue_design_spline_parameter_BEG];
static unsigned char changed[blue_design_spline_parameter_END
                             - blue_design_spline_parameter_BEG];

static unsigned char get_error(blue_design_spline_parameter_t p);
static void set_error(blue_design_spline_parameter_t p);
static void unset_errors(void);

design_spline_s *blue_design_spline_parameter_handler(int argc,
                                                      char** argv,
                                                      design_spline_s *s)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "vertices-xml", 1, 0, blue_design_spline_parameter_vertices_xml },
      { "defaults-xml", 1, 0, blue_design_spline_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  vertices_s *v;
  xmlDocPtr doc;

  if (!s) s = design_spline_create();
  if (!s) return NULL;

  blue_design_spline_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_spline_parameter_vertices_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        v = vertices_from_xml_doc(doc);
        if (v) design_spline_set_vertices(s, v);
        xmlFreeDoc(doc);
        blue_design_spline_set_change(blue_design_spline_parameter_vertices_xml);
        break;
      case blue_design_spline_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_spline_set_change(blue_design_spline_parameter_defaults_xml);
        break;
      default: break;
    }
  }

  blue_design_spline_unset_changes();

  return s;
}

int blue_design_spline_check(design_spline_s *s)
{
  int i;

  assert(s);

  unset_errors();

  for (i = blue_design_spline_parameter_BEG;
       i < blue_design_spline_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_spline_check_error(void)
{
  if (get_error(blue_design_spline_parameter_vertices_xml))
    fprintf(stderr, "Parameter Error; vertices-xml\n");
  if (get_error(blue_design_spline_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_spline_get_change(blue_design_spline_parameter_t p)
{
  return changed[p - blue_design_spline_parameter_BEG];
}

void blue_design_spline_set_change(blue_design_spline_parameter_t p)
{
  changed[p - blue_design_spline_parameter_BEG] = 1;
}

void blue_design_spline_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_spline_parameter_t p)
{
  return errors[p - blue_design_spline_parameter_BEG];
}

static void set_error(blue_design_spline_parameter_t p)
{
  errors[p - blue_design_spline_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

