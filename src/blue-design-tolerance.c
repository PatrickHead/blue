#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"

#include "sieve.h"
#include "blue-design-tolerance-parms.h"
#include "design-tolerance-xml.h"

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
  design_tolerance_s *t;
  char* in_file_name = NULL;
  char* out_file_name = NULL;
  FILE *infile;
  FILE *outfile;
  xmlDocPtr doc;

  LIBXML_TEST_VERSION

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

  t = design_tolerance_sieve(infile, outfile);

  if (infile != stdin) fclose(infile);

    // Process specific command line options

  t = blue_design_tolerance_parameter_handler(argc, argv, t);

  if (blue_design_tolerance_check(t))
  {
    blue_design_tolerance_check_error();
    return -1;
  }

  doc = design_tolerance_to_xml_doc(t);
  if (!doc)
  {
    fprintf(stderr, "Error converting parameters to XML.\n");
    return -1;
  }

  xmlDocFormatDumpEnc(outfile, doc, "UTF-8", 1);

  xmlFreeDoc(doc);
  xmlCleanupParser();

  design_tolerance_destroy(t);

  return 0;
}

static void version(void)
{
  fprintf(stderr, "blue-design-tolerance 0.1\n");
}

#include "blue-design-tolerance-usage.inc"

