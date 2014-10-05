#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/tree.h>

#include "blue-design-line-style-segment-parms.h"

static unsigned char errors[blue_design_line_style_segment_parameter_END
                            - blue_design_line_style_segment_parameter_BEG];
static unsigned char changed[blue_design_line_style_segment_parameter_END
                             - blue_design_line_style_segment_parameter_BEG];

static unsigned char get_error(blue_design_line_style_segment_parameter_t p);
static void set_error(blue_design_line_style_segment_parameter_t p);
static void unset_errors(void);

design_line_style_segment_s *blue_design_line_style_segment_parameter_handler(
  int argc, char** argv, design_line_style_segment_s *lss)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "length", 1, 0, blue_design_line_style_segment_parameter_length },
      { 0, 0, 0, 0 }
    };

  if (!lss) lss = design_line_style_segment_create();
  if (!lss) return NULL;

  blue_design_line_style_segment_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_line_style_segment_parameter_length:
        design_line_style_segment_set_length(lss, strtod(optarg, NULL));
        blue_design_line_style_segment_set_change(
          blue_design_line_style_segment_parameter_length);
        break;
    }
  }

  blue_design_line_style_segment_unset_changes();

  return lss;
}

int blue_design_line_style_segment_check(design_line_style_segment_s *lss)
{
  int i;

  assert(lss);

  unset_errors();

  if (lss->length < 0.0)
    set_error(blue_design_line_style_segment_parameter_length);

  for (i = blue_design_line_style_segment_parameter_BEG;
       i < blue_design_line_style_segment_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_line_style_segment_check_error(void)
{
  if (get_error(blue_design_line_style_segment_parameter_length))
    fprintf(stderr, "Parameter Error; length\n");
}

unsigned char blue_design_line_style_segment_get_change(
  blue_design_line_style_segment_parameter_t p)
{
  return changed[p - blue_design_line_style_segment_parameter_BEG];
}

void blue_design_line_style_segment_set_change(
  blue_design_line_style_segment_parameter_t p)
{
  changed[p - blue_design_line_style_segment_parameter_BEG] = 1;
}

void blue_design_line_style_segment_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_line_style_segment_parameter_t p)
{
  return errors[p - blue_design_line_style_segment_parameter_BEG];
}

static void set_error(blue_design_line_style_segment_parameter_t p)
{
  errors[p - blue_design_line_style_segment_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

