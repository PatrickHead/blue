#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "color-xml.h"

#include "xml-extensions.h"

#include "sieve.h"
#include "blue-color-parms.h"

#define LOCAL_OPTION_BASE 100000

static void version(void);
static void usage(void);

int main(int argc, char** argv)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "mode", 1, 0, LOCAL_OPTION_BASE },
      { "input", 1, 0, LOCAL_OPTION_BASE+1 },
      { "output", 1, 0, LOCAL_OPTION_BASE+2 },
      { "version", 0, 0, 'v' },
      { "help", 0, 0, 'h' },
      { 0, 0, 0, 0 }
    };
  color_s *color = NULL;
  char* in_file_name = NULL;
  char* out_file_name = NULL;
  FILE *infile;
  FILE *outfile;
  xmlDocPtr doc;

  LIBXML_TEST_VERSION

    // Process local command options

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case LOCAL_OPTION_BASE:
        sieve_set_process_mode(str2sieve_process_mode_type(optarg));
        break;

      case LOCAL_OPTION_BASE+1:
        in_file_name = strdup(optarg);
        break;

      case LOCAL_OPTION_BASE+2:
        out_file_name = strdup(optarg);
        break;

      case 'v':
        version();
        return 0;

      case 'h':
        usage();
        return 0;

      case '?':
      default:
        break;
    }
  }

  if (in_file_name && strcmp(in_file_name, "-"))
  {
    infile = fopen(in_file_name, "r");
    free(in_file_name);
  }
  else
    infile = stdin;

  if (out_file_name && strcmp(out_file_name, "-"))
  {
    outfile = fopen(out_file_name, "w");
    free(out_file_name);
  }
  else
    outfile = stdout;

    // Process any XML input documents

  color = color_sieve(infile, outfile);

  if (infile != stdin) fclose(infile);

    // Process specific command line options

  color = blue_color_parameter_handler(argc, argv, color);

  if (blue_color_check(color))
  {
    blue_color_check_error();
    free(in_file_name);
    return -1;
  }

  doc = color_to_xml_doc(color);
  if (!doc)
  {
    fprintf(stderr, "Error converting parameters to XML.\n");
    return -1;
  }

  xmlDocFormatDumpEnc(outfile, doc, "UTF-8", 1);

  xmlFreeDoc(doc);
  xmlCleanupParser();

  return 0;
}

static void version(void)
{
  fprintf(stderr, "blue-color 0.1\n");
}

#include "blue-color-usage.inc"

