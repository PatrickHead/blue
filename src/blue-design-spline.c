/*!
    @file blue-design-spline.c

    @brief SOURCE_BRIEF

    @timestamp Fri, 09 Oct 2015 05:38:21 +0000

    @author Patrick Head  mailto:patrickhead@gmail.com

    @copyright Copyright (C) 2014  Patrick Head

    @license
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.@n
    @n
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.@n
    @n
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

  /*!

    @file blue-design-spline.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

  // Project related headers

#include "xml-extensions.h"

#include "sieve.h"
#include "blue-design-spline-parms.h"
#include "design-spline-xml.h"

#define LOCAL_OPTION_BASE 100000

static void version(void);
static void usage(void);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

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
  design_spline_s *s;
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
          // Return RETVAL
  return 0;

      case 'h':
        usage();
          // Return RETVAL
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

  s = design_spline_sieve(infile, outfile);

  if (infile != stdin) fclose(infile);

    // Process specific command line options

  s = blue_design_spline_parameter_handler(argc, argv, s);

  if (blue_design_spline_check(s))
  {
    blue_design_spline_check_error();
      // Return RETVAL
  return -1;
  }

  doc = design_spline_to_xml_doc(s);
  if (!doc)
  {
    fprintf(stderr, "Error converting parameters to XML.\n");
      // Return RETVAL
  return -1;
  }

  if (!out_file_name) out_file_name = strdup("-");

  xmlDocFormatDumpEnc(outfile, doc, "UTF-8", 1);

  xmlFreeDoc(doc);
  xmlCleanupParser();

  design_spline_destroy(s);

    // Return RETVAL
  return 0;
}

static void version(void)
{
  fprintf(stderr, "blue-design-spline 0.1\n");
}

#include "blue-design-spline-usage.inc"

