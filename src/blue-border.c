#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xml-extensions.h"

#include "blue-border-parms.h"
#include "border-xml.h"

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
      { "input", 1, 0, LOCAL_OPTION_BASE },
      { "output", 1, 0, LOCAL_OPTION_BASE+1 },
      { "version", 0, 0, 'v' },
      { "help", 0, 0, 'h' },
      { 0, 0, 0, 0 }
    };
  border_s *b;
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
        in_file_name = strdup(optarg);
        break;

      case LOCAL_OPTION_BASE+1:
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

  b = border_sieve(infile, outfile);

  if (infile != stdin) fclose(infile);

    // Process specific command line options

  b = blue_border_parameter_handler(argc, argv, b);

  if (blue_border_check(b))
  {
    blue_border_check_error();
    return -1;
  }

  doc = border_to_xml_doc(b);
  if (!doc)
  {
    fprintf(stderr, "Error converting parameters to XML.\n");
    return -1;
  }

  if (!out_file_name) out_file_name = strdup("-");

  xmlDocFormatDumpEnc(outfile, doc, "UTF-8", 1);

  xmlFreeDoc(doc);
  xmlCleanupParser();

  border_destroy(b);

  return 0;
}

static void version(void)
{
  fprintf(stderr, "blue-border 0.1\n");
}

#include "blue-border-usage.inc"

