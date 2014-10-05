#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "units.h"

#include "design-defaults-xml.h"

#include "blue-design-elliptic-parms.h"

static unsigned char errors[blue_design_elliptic_parameter_END
                            - blue_design_elliptic_parameter_BEG];
static unsigned char changed[blue_design_elliptic_parameter_END
                             - blue_design_elliptic_parameter_BEG];

static unsigned char get_error(blue_design_elliptic_parameter_t p);
static void set_error(blue_design_elliptic_parameter_t p);
static void unset_errors(void);

design_elliptic_s *blue_design_elliptic_parameter_handler(int argc,
                                                          char** argv,
                                                          design_elliptic_s *e)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "center", 1, 0, blue_design_elliptic_parameter_center },
      { "width", 1, 0, blue_design_elliptic_parameter_width },
      { "height", 1, 0, blue_design_elliptic_parameter_height },
      { "rotation", 1, 0, blue_design_elliptic_parameter_rotation },
      { "start-angle", 1, 0, blue_design_elliptic_parameter_start_angle },
      { "end-angle", 1, 0, blue_design_elliptic_parameter_end_angle },
      { "defaults-xml", 1, 0, blue_design_elliptic_parameter_defaults_xml },
      { 0, 0, 0, 0 }
    };
  design_defaults_s *d;
  xmlDocPtr doc;

  if (!e) e = design_elliptic_create();
  if (!e) return NULL;

  blue_design_elliptic_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_elliptic_parameter_center:
        design_elliptic_set_center(e, str2vertex(optarg));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_center);
        break;
      case blue_design_elliptic_parameter_width:
        design_elliptic_set_width(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_width);
        break;
      case blue_design_elliptic_parameter_height:
        design_elliptic_set_height(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_height);
        break;
      case blue_design_elliptic_parameter_rotation:
        design_elliptic_set_rotation(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_rotation);
        break;
      case blue_design_elliptic_parameter_start_angle:
        design_elliptic_set_start_angle(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(
          blue_design_elliptic_parameter_start_angle);
        break;
      case blue_design_elliptic_parameter_end_angle:
        design_elliptic_set_end_angle(e, strtod(optarg, NULL));
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_end_angle);
        break;
      case blue_design_elliptic_parameter_defaults_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        d = design_defaults_from_xml_doc(doc);
        if (d) design_defaults_push(d);
        xmlFreeDoc(doc);
        blue_design_elliptic_set_change(blue_design_elliptic_parameter_defaults_xml);
        break;
    }
  }

  blue_design_elliptic_unset_changes();

  return e;
}

int blue_design_elliptic_check(design_elliptic_s *e)
{
  int i;

  assert(e);

  unset_errors();

  if (e->width < 0.0) set_error(blue_design_elliptic_parameter_width);
  if (e->height < 0.0) set_error(blue_design_elliptic_parameter_height);
  if (e->rotation < 0.0) set_error(blue_design_elliptic_parameter_rotation);
  if (e->start_angle < 0.0) set_error(blue_design_elliptic_parameter_start_angle);
  if (e->end_angle < 0.0) set_error(blue_design_elliptic_parameter_end_angle);

  for (i = blue_design_elliptic_parameter_BEG;
       i < blue_design_elliptic_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_elliptic_check_error(void)
{
  if (get_error(blue_design_elliptic_parameter_center))
    fprintf(stderr, "Parameter Error; center\n");
  if (get_error(blue_design_elliptic_parameter_width))
    fprintf(stderr, "Parameter Error; width\n");
  if (get_error(blue_design_elliptic_parameter_height))
    fprintf(stderr, "Parameter Error; height\n");
  if (get_error(blue_design_elliptic_parameter_rotation))
    fprintf(stderr, "Parameter Error; rotation\n");
  if (get_error(blue_design_elliptic_parameter_start_angle))
    fprintf(stderr, "Parameter Error; start-angle\n");
  if (get_error(blue_design_elliptic_parameter_end_angle))
    fprintf(stderr, "Parameter Error; end-angle\n");
  if (get_error(blue_design_elliptic_parameter_defaults_xml))
    fprintf(stderr, "Parameter Error; defaults-xml\n");
}

unsigned char blue_design_elliptic_get_change(blue_design_elliptic_parameter_t p)
{
  return changed[p - blue_design_elliptic_parameter_BEG];
}

void blue_design_elliptic_set_change(blue_design_elliptic_parameter_t p)
{
  changed[p - blue_design_elliptic_parameter_BEG] = 1;
}

void blue_design_elliptic_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_elliptic_parameter_t p)
{
  return errors[p - blue_design_elliptic_parameter_BEG];
}

static void set_error(blue_design_elliptic_parameter_t p)
{
  errors[p - blue_design_elliptic_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

