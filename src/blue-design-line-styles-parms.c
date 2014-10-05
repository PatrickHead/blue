#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "units.h"
#include "design-line-styles-xml.h"

#include "blue-design-line-styles-parms.h"

static unsigned char errors[blue_design_line_styles_parameter_END
                            - blue_design_line_styles_parameter_BEG];
static unsigned char changed[blue_design_line_styles_parameter_END
                             - blue_design_line_styles_parameter_BEG];

static unsigned char get_error(blue_design_line_styles_parameter_t p);
static void set_error(blue_design_line_styles_parameter_t p);
static void unset_errors(void);

design_line_styles_s *blue_design_line_styles_parameter_handler(int argc,
                                                                char** argv,
                                                        design_line_styles_s *lss)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "line-style-xml",
        1,
        0,
        blue_design_line_styles_parameter_line_style_xml },
      { 0, 0, 0, 0 }
    };
  design_line_style_s *ls;
  xmlDocPtr doc;

  if (!lss) lss = design_line_styles_create();
  if (!lss) return NULL;

  blue_design_line_styles_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_line_styles_parameter_line_style_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        ls = design_line_style_from_xml_doc(doc);
        if (ls)
          design_line_styles_add_line_style(lss, ls);
        xmlFreeDoc(doc);
        blue_design_line_styles_set_change(
          blue_design_line_styles_parameter_line_style_xml);
        break;
      default: break;
    }
  }

  blue_design_line_styles_unset_changes();

  return lss;
}

int blue_design_line_styles_check(design_line_styles_s *lss)
{
  int i;

  assert(lss);

  unset_errors();

  for (i = blue_design_line_styles_parameter_BEG;
       i < blue_design_line_styles_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_line_styles_check_error(void)
{
}

unsigned char blue_design_line_styles_get_change(
  blue_design_line_styles_parameter_t p)
{
  return changed[p - blue_design_line_styles_parameter_BEG];
}

void blue_design_line_styles_set_change(
  blue_design_line_styles_parameter_t p)
{
  changed[p - blue_design_line_styles_parameter_BEG] = 1;
}

void blue_design_line_styles_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_line_styles_parameter_t p)
{
  return errors[p - blue_design_line_styles_parameter_BEG];
}

static void set_error(blue_design_line_styles_parameter_t p)
{
  errors[p - blue_design_line_styles_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

