#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#include "blue-color-parms.h"

static unsigned char errors[blue_color_parameter_END - blue_color_parameter_BEG];
static unsigned char changed[blue_color_parameter_END - blue_color_parameter_BEG];

static unsigned char get_error(blue_color_parameter_t p);
static void set_error(blue_color_parameter_t p);
static void unset_errors(void);

color_s *blue_color_parameter_handler(int argc, char** argv, color_s *color)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "tag", 1, 0, blue_color_parameter_tag },
      { "r", 1, 0, blue_color_parameter_r },
      { "g", 1, 0, blue_color_parameter_g },
      { "b", 1, 0, blue_color_parameter_b },
      { "a", 1, 0, blue_color_parameter_a },
      { 0, 0, 0, 0 }
    };

  if (!color) color = color_create();
  if (!color) return NULL;

  blue_color_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_color_parameter_tag:
        color->tag = strdup(optarg);
        blue_color_set_change(blue_color_parameter_tag);
        break;
      case blue_color_parameter_r:
        color->r = strtod(optarg, NULL);
        blue_color_set_change(blue_color_parameter_r);
        break;
      case blue_color_parameter_g:
        color->g = strtod(optarg, NULL);
        blue_color_set_change(blue_color_parameter_g);
        break;
      case blue_color_parameter_b:
        color->b = strtod(optarg, NULL);
        blue_color_set_change(blue_color_parameter_b);
        break;
      case blue_color_parameter_a:
        color->a = strtod(optarg, NULL);
        blue_color_set_change(blue_color_parameter_a);
        break;
    }
  }

  blue_color_unset_changes();

  return color;
}

int blue_color_check(color_s *color)
{
  int i;

  assert(color);

  unset_errors();

  if ((color->r < 0.0) || (color->r > 255.0)) set_error(blue_color_parameter_r);
  if ((color->g < 0.0) || (color->g > 255.0)) set_error(blue_color_parameter_g);
  if ((color->b < 0.0) || (color->b > 255.0)) set_error(blue_color_parameter_b);
  if ((color->a < 0.0) || (color->a > 255.0)) set_error(blue_color_parameter_a);

  for (i = blue_color_parameter_BEG; i < blue_color_parameter_END; i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_color_check_error(void)
{
  if (get_error(blue_color_parameter_tag))
    fprintf(stderr, "Parameter Error; tag\n");
  if (get_error(blue_color_parameter_r))
    fprintf(stderr, "Parameter Error; r\n");
  if (get_error(blue_color_parameter_g))
    fprintf(stderr, "Parameter Error; g\n");
  if (get_error(blue_color_parameter_b))
    fprintf(stderr, "Parameter Error; b\n");
  if (get_error(blue_color_parameter_a))
    fprintf(stderr, "Parameter Error; a\n");
}

unsigned char blue_color_get_change(blue_color_parameter_t p)
{
  return changed[p - blue_color_parameter_BEG];
}

void blue_color_set_change(blue_color_parameter_t p)
{
  changed[p - blue_color_parameter_BEG] = 1;
}

void blue_color_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_color_parameter_t p)
{
  return errors[p - blue_color_parameter_BEG];
}

static void set_error(blue_color_parameter_t p)
{
  errors[p - blue_color_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

