#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <getopt.h>
#include <assert.h>
#include <cairo.h>
#include <cairo-svg.h>
#include <cairo-pdf.h>
#include <cairo-ps.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "drawing-xml.h"
#include "render-2d-cairo.h"

#define LOCAL_OPTION_BASE 10000

typedef enum
{
  blue_option_backend_type = LOCAL_OPTION_BASE,
  blue_option_cairo_output_type,
  blue_option_output_file_name
} blue_option;

typedef enum
{
  blue_backend_type_cairo,
  blue_backend_type_dxf
} blue_backend_type;

typedef enum
{
  cairo_output_type_svg,
  cairo_output_type_pdf,
  cairo_output_type_ps,
  cairo_output_type_png
} cairo_output_type;

static void version(void);
static void usage(void);

static blue_backend_type str2blue_backend_type(char *s);
static char *blue_backend_type2str(blue_backend_type t);
static cairo_output_type str2cairo_output_type(char *s);
static char *cairo_output_type2str(cairo_output_type t);
static char *fix_input_file_name(char *fn);

/*
1. Pick up blueXML file
2. render to appropriate backend
3. options:
  a. output file
  b. render backend
  c. backend file format
  NOTE:  currently, only cairo, with SVG, PDF, PNG and PS are available
  NOTE:  DXF option support, with real support to be added later
*/

int main(int argc, char** argv)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "backend", 1, 0, blue_option_backend_type },
      { "cairo-format", 1, 0, blue_option_cairo_output_type },
      { "output", 1, 0, blue_option_output_file_name },
      { "version", 0, 0, 'v' },
      { "help", 0, 0, 'h' },
      { 0, 0, 0, 0 }
    };
  char* input_file_name = NULL;
  char* output_file_name = NULL;
  blue_backend_type backend = blue_backend_type_cairo;
  cairo_output_type cairo_output = cairo_output_type_svg;
  xmlDocPtr doc;
  drawing_s *drawing;
  cairo_surface_t *drawing_surface;
  cairo_surface_t *render_surface;
  cairo_t *render_context;
  cairo_rectangle_t drawing_size;

  LIBXML_TEST_VERSION

  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_option_backend_type:
        backend = str2blue_backend_type(optarg);
        break;

      case blue_option_cairo_output_type:
        cairo_output = str2cairo_output_type(optarg);
        break;

      case blue_option_output_file_name:
        output_file_name = strdup(optarg);
        break;

      case 'v':
        version();
        return 0;

      case 'h':
      case '?':
        usage();
        return 0;

      default:
        break;
    }
  }

  if (optind < argc)
    input_file_name = fix_input_file_name(argv[optind]);

  if (!input_file_name)
    input_file_name = strdup("-");

  //if (!output_file_name) output_file_name = strdup("-");

  doc = xmlReadFile(input_file_name, "UTF-8", 0);
  if (!doc)
  {
    fprintf(stderr, "Error reading XML file.\n");
    return -1;
  }

  drawing = drawing_from_xml_doc(doc);
  if (drawing)
  {
    switch (backend)
    {
      case blue_backend_type_cairo:
        drawing_surface = render_2d_cairo(drawing);
        if (!drawing_surface)
          break;

        get_surface_size(drawing_surface, &drawing_size);

        switch (cairo_output)
        {
          case cairo_output_type_svg:
            render_surface = cairo_svg_surface_create(output_file_name,
                                                      drawing_size.width,
                                                      drawing_size.height);
            break;
          case cairo_output_type_pdf:
            render_surface = cairo_pdf_surface_create(output_file_name,
                                                      drawing_size.width,
                                                      drawing_size.height);
            break;
          case cairo_output_type_ps:
            render_surface = cairo_ps_surface_create(output_file_name,
                                                     drawing_size.width,
                                                     drawing_size.height);
            break;
          case cairo_output_type_png:
            break;
          default: break;
        }
        if (!render_surface)
          break;

        render_context = cairo_create(render_surface);
        if (!render_context)
          break;

        cairo_set_source_surface(render_context, drawing_surface, 0.0, 0.0);
        cairo_paint(render_context);
        cairo_show_page(render_context);

        break;

      case blue_backend_type_dxf:

        break;
    }

    if (render_context)
      cairo_destroy(render_context);
    if (drawing_surface)
      cairo_surface_destroy(drawing_surface);
    if (render_surface)
      cairo_surface_destroy(render_surface);
  }

  if (drawing) drawing_destroy(drawing);
  if (doc) xmlFreeDoc(doc);
  if (output_file_name) free(output_file_name);
  if (input_file_name) free(input_file_name);

  xmlCleanupParser();

  return 0;
}

static void version(void)
{
  fprintf(stderr, "blue 0.1\n");
}

#include "blue-render-usage.inc"

static blue_backend_type str2blue_backend_type(char *s)
{
  assert(s);

  if (!strcmp(s, "cairo")) return blue_backend_type_cairo;
  if (!strcmp(s, "dxf")) return blue_backend_type_dxf;

  return blue_backend_type_cairo;
}

static char *blue_backend_type2str(blue_backend_type t)
{
  switch (t)
  {
    case blue_backend_type_cairo: return "cairo";
    case blue_backend_type_dxf: return "dxf";
    default: break;
  }

  return "cairo";
}

static cairo_output_type str2cairo_output_type(char *s)
{
  assert(s);

  if (!strcmp(s, "svg")) return cairo_output_type_svg;
  if (!strcmp(s, "pdf")) return cairo_output_type_pdf;
  if (!strcmp(s, "ps")) return cairo_output_type_ps;
  if (!strcmp(s, "png")) return cairo_output_type_png;

  return cairo_output_type_svg;
}

static char *cairo_output_type2str(cairo_output_type t)
{
  switch (t)
  {
    case cairo_output_type_svg: return "svg";
    case cairo_output_type_pdf: return "pdf";
    case cairo_output_type_ps: return "ps";
    case cairo_output_type_png: return "png";
    default: break;
  }

  return "svg";
}

static char *fix_input_file_name(char *fn)
{
  char *bn;
  char *dot;
  char *new_fn;

  assert(fn);

  if (!strcmp(fn, "-"))
    return strdup(fn);

  bn = basename(fn);
  if (bn)
  {
    dot = strrchr(bn, '.');
    if (dot)
    {
      ++dot;
      if (!strcasecmp(dot, "xml"))
        return strdup(fn);
    }
    new_fn = (char *)malloc(strlen(fn) + 5);
    sprintf(new_fn, "%s.xml", fn);
    return new_fn;
  }

  return NULL;
}

