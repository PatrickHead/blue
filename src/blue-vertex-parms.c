#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#include "blue-vertex-parms.h"

static unsigned char errors[blue_vertex_parameter_END - blue_vertex_parameter_BEG];
static unsigned char changed[blue_vertex_parameter_END - blue_vertex_parameter_BEG];

static unsigned char get_error(blue_vertex_parameter_t p);
static void set_error(blue_vertex_parameter_t p);
static void unset_errors(void);

vertex_s *blue_vertex_parameter_handler(int argc, char** argv, vertex_s *v)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "tag", 1, 0, blue_vertex_parameter_tag },
      { "x", 1, 0, blue_vertex_parameter_x },
      { "y", 1, 0, blue_vertex_parameter_y },
      { "z", 1, 0, blue_vertex_parameter_z },
      { 0, 0, 0, 0 }
    };

  if (!v) v = vertex_create();
  if (!v) return NULL;

  blue_vertex_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_vertex_parameter_tag:
        v->tag = strdup(optarg);
        blue_vertex_set_change(blue_vertex_parameter_tag);
        break;
      case blue_vertex_parameter_x:
        v->x = strtod(optarg, NULL);
        blue_vertex_set_change(blue_vertex_parameter_x);
        break;
      case blue_vertex_parameter_y:
        v->y = strtod(optarg, NULL);
        blue_vertex_set_change(blue_vertex_parameter_y);
        break;
      case blue_vertex_parameter_z:
        v->z = strtod(optarg, NULL);
        blue_vertex_set_change(blue_vertex_parameter_z);
        break;
    }
  }

  blue_vertex_unset_changes();

  return v;
}

int blue_vertex_check(vertex_s *v)
{
  int i;

  assert(v);

  unset_errors();

  for (i = blue_vertex_parameter_BEG; i < blue_vertex_parameter_END; i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_vertex_check_error(void)
{
  if (get_error(blue_vertex_parameter_tag))
    fprintf(stderr, "Parameter Error; tag\n");
  if (get_error(blue_vertex_parameter_x))
    fprintf(stderr, "Parameter Error; x\n");
  if (get_error(blue_vertex_parameter_y))
    fprintf(stderr, "Parameter Error; x\n");
  if (get_error(blue_vertex_parameter_z))
    fprintf(stderr, "Parameter Error; x\n");
}

unsigned char blue_vertex_get_change(blue_vertex_parameter_t p)
{
  return changed[p - blue_vertex_parameter_BEG];
}

void blue_vertex_set_change(blue_vertex_parameter_t p)
{
  changed[p - blue_vertex_parameter_BEG] = 1;
}

void blue_vertex_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_vertex_parameter_t p)
{
  return errors[p - blue_vertex_parameter_BEG];
}

static void set_error(blue_vertex_parameter_t p)
{
  errors[p - blue_vertex_parameter_BEG] = 1;
}

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

