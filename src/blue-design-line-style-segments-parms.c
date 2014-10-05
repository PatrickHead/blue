#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "units.h"
#include "design-line-style-segments-xml.h"

#include "blue-design-line-style-segments-parms.h"

static unsigned char errors[blue_design_line_style_segments_parameter_END
                            - blue_design_line_style_segments_parameter_BEG];
static unsigned char changed[blue_design_line_style_segments_parameter_END
                             - blue_design_line_style_segments_parameter_BEG];

static unsigned char get_error(blue_design_line_style_segments_parameter_t p);
static void set_error(blue_design_line_style_segments_parameter_t p);
static void unset_errors(void);

design_line_style_segments_s *blue_design_line_style_segments_parameter_handler(
  int argc, char** argv, design_line_style_segments_s *lsss)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "segment-xml",
        1,
        0,
        blue_design_line_style_segments_parameter_segment_xml },
      { 0, 0, 0, 0 }
    };
  design_line_style_segment_s *lss;
  xmlDocPtr doc;

  if (!lsss) lsss = design_line_style_segments_create();
  if (!lsss) return NULL;

  blue_design_line_style_segments_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_line_style_segments_parameter_segment_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        lss = design_line_style_segment_from_xml_doc(doc);
        design_line_style_segments_add_line_style_segment(lsss, lss);
        xmlFreeDoc(doc);
        blue_design_line_style_segments_set_change(
          blue_design_line_style_segments_parameter_segment_xml);
        break;
      default: break;
    }
  }

  blue_design_line_style_segments_unset_changes();

  return lsss;
}

int blue_design_line_style_segments_check(design_line_style_segments_s *lsss)
{
  int i;

  assert(lsss);

  unset_errors();

  for (i = blue_design_line_style_segments_parameter_BEG;
       i < blue_design_line_style_segments_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_line_style_segments_check_error(void)
{
  if (get_error(blue_design_line_style_segments_parameter_segment_xml))
    fprintf(stderr, "Parameter Error; segment-xml\n");
}

unsigned char blue_design_line_style_segments_get_change(
  blue_design_line_style_segments_parameter_t p)
{
  return changed[p - blue_design_line_style_segments_parameter_BEG];
}

void blue_design_line_style_segments_set_change(
  blue_design_line_style_segments_parameter_t p)
{
  changed[p - blue_design_line_style_segments_parameter_BEG] = 1;
}

void blue_design_line_style_segments_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_line_style_segments_parameter_t p)
{
  return errors[p - blue_design_line_style_segments_parameter_BEG];
}

static void set_error(blue_design_line_style_segments_parameter_t p)
{
  errors[p - blue_design_line_style_segments_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

