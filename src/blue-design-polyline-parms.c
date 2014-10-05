#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "units.h"

#include "vertices-xml.h"
#include "design-defaults-xml.h"

#include "blue-design-polyline-parms.h"

static unsigned char errors[blue_design_polyline_parameter_END
                            - blue_design_polyline_parameter_BEG];
static unsigned char changed[blue_design_polyline_parameter_END
                             - blue_design_polyline_parameter_BEG];

static unsigned char get_error(blue_design_polyline_parameter_t p);
static void set_error(blue_design_polyline_parameter_t p);
static void unset_errors(void);

design_polyline_s *blue_design_polyline_parameter_handler(int argc,
                                                          char** argv,
                                                          design_polyline_s *pl)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "vertices-xml", 1, 0, blue_design_polyline_parameter_vertices_xml },
      { "defaults-xml", 1, 0, blue_design_polyline_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  vertices_s *v;
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!pl) pl = design_polyline_create();
  if (!pl) return NULL;

  blue_design_polyline_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_polyline_parameter_vertices_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        v = vertices_from_xml_doc(doc);
        if (v) design_polyline_set_vertices(pl, v);
        xmlFreeDoc(doc);
        blue_design_polyline_set_change(
          blue_design_polyline_parameter_vertices_xml);
        break;
      case blue_design_polyline_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_polyline_set_change(
          blue_design_polyline_parameter_defaults_xml);
        break;
      default: break;
    }
  }

  blue_design_polyline_unset_changes();

  return pl;
}

int blue_design_polyline_check(design_polyline_s *pl)
{
  int i;

  assert(pl);

  unset_errors();

  for (i = blue_design_polyline_parameter_BEG;
       i < blue_design_polyline_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_polyline_check_error(void)
{
  if (get_error(blue_design_polyline_parameter_vertices_xml))
    fprintf(stderr, "Parameter Error; vertices-xml\n");
  if (get_error(blue_design_polyline_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_polyline_get_change(blue_design_polyline_parameter_t p)
{
  return changed[p - blue_design_polyline_parameter_BEG];
}

void blue_design_polyline_set_change(blue_design_polyline_parameter_t p)
{
  changed[p - blue_design_polyline_parameter_BEG] = 1;
}

void blue_design_polyline_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_polyline_parameter_t p)
{
  return errors[p - blue_design_polyline_parameter_BEG];
}

static void set_error(blue_design_polyline_parameter_t p)
{
  errors[p - blue_design_polyline_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

