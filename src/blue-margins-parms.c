#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#include "blue-margins-parms.h"

static unsigned char errors[blue_margins_parameter_END - blue_margins_parameter_BEG];
static unsigned char changed[blue_margins_parameter_END - blue_margins_parameter_BEG];

static unsigned char get_error(blue_margins_parameter_t p);
static void set_error(blue_margins_parameter_t p);
static void unset_errors(void);

margins_s *blue_margins_parameter_handler(int argc, char** argv, margins_s *m)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "units", 1, 0, blue_margins_parameter_units },
      { "top", 1, 0, blue_margins_parameter_top },
      { "bottom", 1, 0, blue_margins_parameter_bottom },
      { "left", 1, 0, blue_margins_parameter_left },
      { "right", 1, 0, blue_margins_parameter_right },
      { 0, 0, 0, 0 }
    };

  if (!m) m = margins_create();
  if (!m) return NULL;

  blue_margins_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_margins_parameter_units:
        margins_set_units(m, str2units(optarg));
        blue_margins_set_change(blue_margins_parameter_units);
        break;
      case blue_margins_parameter_top:
        margins_set_top(m, strtod(optarg, NULL));
        blue_margins_set_change(blue_margins_parameter_top);
        break;
      case blue_margins_parameter_bottom:
        margins_set_bottom(m, strtod(optarg, NULL));
        blue_margins_set_change(blue_margins_parameter_bottom);
        break;
      case blue_margins_parameter_left:
        margins_set_left(m, strtod(optarg, NULL));
        blue_margins_set_change(blue_margins_parameter_left);
        break;
      case blue_margins_parameter_right:
        margins_set_right(m, strtod(optarg, NULL));
        blue_margins_set_change(blue_margins_parameter_right);
        break;
    }
  }

  blue_margins_unset_changes();

  return m;
}

int blue_margins_check(margins_s *m)
{
  int i;

  assert(m);

  unset_errors();

  if (m->top < 0.0) set_error(blue_margins_parameter_top);
  if (m->bottom < 0.0) set_error(blue_margins_parameter_bottom);
  if (m->left < 0.0) set_error(blue_margins_parameter_left);
  if (m->right < 0.0) set_error(blue_margins_parameter_right);

  for (i = blue_margins_parameter_BEG; i < blue_margins_parameter_END; i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_margins_check_error(void)
{
  if (get_error(blue_margins_parameter_units))
    fprintf(stderr, "Parameter Error; units\n");
  if (get_error(blue_margins_parameter_top))
    fprintf(stderr, "Parameter Error; margin-top\n");
  if (get_error(blue_margins_parameter_bottom))
    fprintf(stderr, "Parameter Error; margin-bottom\n");
  if (get_error(blue_margins_parameter_left))
    fprintf(stderr, "Parameter Error; margin-left\n");
  if (get_error(blue_margins_parameter_right))
    fprintf(stderr, "Parameter Error; margin-right\n");
}

unsigned char blue_margins_get_change(blue_margins_parameter_t p)
{
  return changed[p - blue_margins_parameter_BEG];
}

void blue_margins_set_change(blue_margins_parameter_t p)
{
  changed[p - blue_margins_parameter_BEG] = 1;
}

void blue_margins_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_margins_parameter_t p)
{
  return errors[p - blue_margins_parameter_BEG];
}

static void set_error(blue_margins_parameter_t p)
{
  errors[p - blue_margins_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

