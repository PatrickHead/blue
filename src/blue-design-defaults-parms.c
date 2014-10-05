#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#include "blue-design-defaults-parms.h"

static unsigned char errors[blue_design_defaults_parameter_END
                            - blue_design_defaults_parameter_BEG];
static unsigned char changed[blue_design_defaults_parameter_END
                             - blue_design_defaults_parameter_BEG];

static unsigned char get_error(blue_design_defaults_parameter_t p);
static void set_error(blue_design_defaults_parameter_t p);
static void unset_errors(void);

design_defaults_s *blue_design_defaults_parameter_handler(int argc,
                                                          char** argv,
                                                          design_defaults_s *d)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "units", 1, 0, blue_design_defaults_parameter_units },
      { "line-weight", 1, 0, blue_design_defaults_parameter_line_weight },
      { "line-style", 1, 0, blue_design_defaults_parameter_line_style },
      { "fill-style", 1, 0, blue_design_defaults_parameter_fill_style },
      { "dimension-text-size", 1, 0,
        blue_design_defaults_parameter_dimension_text_size },
      { "dimension-precision", 1, 0,
        blue_design_defaults_parameter_dimension_precision },
      { "angular-gap", 1, 0,
        blue_design_defaults_parameter_angular_gap },
      { "angular-extension", 1, 0,
        blue_design_defaults_parameter_angular_extension },
      { "linear-gap", 1, 0,
        blue_design_defaults_parameter_linear_gap },
      { "linear-extension-above", 1, 0,
        blue_design_defaults_parameter_linear_extension_above },
      { "linear-extension-below", 1, 0,
        blue_design_defaults_parameter_linear_extension_below },
      { "tolerance-text-size", 1, 0,
        blue_design_defaults_parameter_tolerance_text_size },
      { "tolerance-plus", 1, 0,
        blue_design_defaults_parameter_tolerance_plus },
      { "tolerance-minus", 1, 0,
        blue_design_defaults_parameter_tolerance_minus },
      { "tolerance-precision", 1, 0,
        blue_design_defaults_parameter_tolerance_precision },
      { "background-color-xml", 1, 0,
        blue_design_defaults_parameter_background_color_xml },
      { "element-color-xml", 1, 0,
        blue_design_defaults_parameter_element_color_xml },
      { 0, 0, 0, 0 }
    };

  if (!d) d = design_defaults_create();
  if (!d) return NULL;

  blue_design_defaults_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_design_defaults_parameter_units:
        design_defaults_set_units(d, str2units(optarg));
        blue_design_defaults_set_change(blue_design_defaults_parameter_units);
        break;
      case blue_design_defaults_parameter_line_weight:
        design_defaults_set_line_weight(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_line_weight);
        break;
      case blue_design_defaults_parameter_line_style:
        design_defaults_set_line_style(d, optarg);
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_line_style);
        break;
      case blue_design_defaults_parameter_fill_style:
        design_defaults_set_fill_style(d, optarg);
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_fill_style);
        break;
      case blue_design_defaults_parameter_dimension_text_size:
        design_defaults_set_dimension_text_size(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_dimension_text_size);
        break;
      case blue_design_defaults_parameter_dimension_precision:
        design_defaults_set_dimension_precision(d, strtol(optarg, NULL, 10));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_dimension_precision);
        break;
      case blue_design_defaults_parameter_angular_gap:
        design_defaults_set_angular_gap(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_angular_gap);
        break;
      case blue_design_defaults_parameter_angular_extension:
        design_defaults_set_angular_extension(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_angular_extension);
        break;
      case blue_design_defaults_parameter_linear_gap:
        design_defaults_set_linear_gap(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_linear_gap);
        break;
      case blue_design_defaults_parameter_linear_extension_above:
        design_defaults_set_linear_extension_above(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_linear_extension_above);
        break;
      case blue_design_defaults_parameter_linear_extension_below:
        design_defaults_set_linear_extension_below(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_linear_extension_below);
        break;
      case blue_design_defaults_parameter_tolerance_text_size:
        design_defaults_set_tolerance_text_size(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_tolerance_text_size);
        break;
      case blue_design_defaults_parameter_tolerance_plus:
        design_defaults_set_tolerance_plus(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_tolerance_plus);
        break;
      case blue_design_defaults_parameter_tolerance_minus:
        design_defaults_set_tolerance_minus(d, strtod(optarg, NULL));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_tolerance_minus);
        break;
      case blue_design_defaults_parameter_tolerance_precision:
        design_defaults_set_tolerance_precision(d, strtol(optarg, NULL, 10));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_tolerance_precision);
        break;
      case blue_design_defaults_parameter_background_color_xml:
        design_defaults_set_background_color(d, str2color(optarg));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_background_color_xml);
        break;
      case blue_design_defaults_parameter_element_color_xml:
        design_defaults_set_element_color(d, str2color(optarg));
        blue_design_defaults_set_change(
          blue_design_defaults_parameter_element_color_xml);
        break;
      default: break;
    }
  }

  blue_design_defaults_unset_changes();

  return d;
}

int blue_design_defaults_check(design_defaults_s *d)
{
  int i;

  assert(d);

  unset_errors();

  if (d->line_weight < 0.0)
    set_error(blue_design_defaults_parameter_line_weight);
  if (d->dimension_text_size < 0.0)
    set_error(blue_design_defaults_parameter_dimension_text_size);
  if (d->dimension_precision < 0)
    set_error(blue_design_defaults_parameter_dimension_precision);
  if (d->angular_gap < 0.0)
    set_error(blue_design_defaults_parameter_angular_gap);
  if (d->angular_extension < 0.0)
    set_error(blue_design_defaults_parameter_angular_extension);
  if (d->linear_gap < 0.0)
    set_error(blue_design_defaults_parameter_linear_gap);
  if (d->linear_extension_above < 0.0)
    set_error(blue_design_defaults_parameter_linear_extension_above);
  if (d->linear_extension_below < 0.0)
    set_error(blue_design_defaults_parameter_linear_extension_below);
  if (d->tolerance_text_size < 0.0)
    set_error(blue_design_defaults_parameter_tolerance_text_size);
  if (d->tolerance_plus < 0.0)
    set_error(blue_design_defaults_parameter_tolerance_plus);
  if (d->tolerance_minus < 0.0)
    set_error(blue_design_defaults_parameter_tolerance_minus);
  if (d->tolerance_precision < 0)
    set_error(blue_design_defaults_parameter_tolerance_precision);

  for (i = blue_design_defaults_parameter_BEG;
       i < blue_design_defaults_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_design_defaults_check_error(void)
{
  if (get_error(blue_design_defaults_parameter_units))
    fprintf(stderr, "Parameter Error; units\n");
  if (get_error(blue_design_defaults_parameter_line_weight))
    fprintf(stderr, "Parameter Error; line-weight\n");
  if (get_error(blue_design_defaults_parameter_line_style))
    fprintf(stderr, "Parameter Error; line-style\n");
  if (get_error(blue_design_defaults_parameter_fill_style))
    fprintf(stderr, "Parameter Error; fill-style\n");
  if (get_error(blue_design_defaults_parameter_dimension_text_size))
    fprintf(stderr, "Parameter Error; dimension-text-size\n");
  if (get_error(blue_design_defaults_parameter_dimension_precision))
    fprintf(stderr, "Parameter Error; dimension-precision\n");
  if (get_error(blue_design_defaults_parameter_angular_gap))
    fprintf(stderr, "Parameter Error; angular-gap\n");
  if (get_error(blue_design_defaults_parameter_angular_extension))
    fprintf(stderr, "Parameter Error; angular-extension\n");
  if (get_error(blue_design_defaults_parameter_linear_gap))
    fprintf(stderr, "Parameter Error; linear-gap\n");
  if (get_error(blue_design_defaults_parameter_linear_extension_above))
    fprintf(stderr, "Parameter Error; linear-extension-above\n");
  if (get_error(blue_design_defaults_parameter_linear_extension_below))
    fprintf(stderr, "Parameter Error; linear-extension-below\n");
  if (get_error(blue_design_defaults_parameter_tolerance_text_size))
    fprintf(stderr, "Parameter Error; tolerance-text-size\n");
  if (get_error(blue_design_defaults_parameter_tolerance_plus))
    fprintf(stderr, "Parameter Error; tolerance-plus\n");
  if (get_error(blue_design_defaults_parameter_tolerance_minus))
    fprintf(stderr, "Parameter Error; tolerance-minus\n");
  if (get_error(blue_design_defaults_parameter_tolerance_precision))
    fprintf(stderr, "Parameter Error; tolerance-precision\n");
  if (get_error(blue_design_defaults_parameter_background_color_xml))
    fprintf(stderr, "Parameter Error; background-color-xml\n");
  if (get_error(blue_design_defaults_parameter_element_color_xml))
    fprintf(stderr, "Parameter Error; element-color-xml\n");
}

unsigned char blue_design_defaults_get_change(blue_design_defaults_parameter_t p)
{
  return changed[p - blue_design_defaults_parameter_BEG];
}

void blue_design_defaults_set_change(blue_design_defaults_parameter_t p)
{
  changed[p - blue_design_defaults_parameter_BEG] = 1;
}

void blue_design_defaults_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_design_defaults_parameter_t p)
{
  return errors[p - blue_design_defaults_parameter_BEG];
}

static void set_error(blue_design_defaults_parameter_t p)
{
  errors[p - blue_design_defaults_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

