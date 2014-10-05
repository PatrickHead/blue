#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "color-xml.h"

#include "blue-title-block-parms.h"

static unsigned char errors[blue_title_block_parameter_END
                            - blue_title_block_parameter_BEG];
static unsigned char changed[blue_title_block_parameter_END
                             - blue_title_block_parameter_BEG];

static unsigned char get_error(blue_title_block_parameter_t p);
/* Currently unused
static void set_error(blue_title_block_parameter_t p);
*/
static void unset_errors(void);
static time_t convert_iso_8601(char *iso_8601_time);

title_block_s *blue_title_block_parameter_handler(int argc,
                                                  char** argv,
                                                  title_block_s *tb)
{
  int c;
  extern char* optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "title", 1, 0, blue_title_block_parameter_title },
      { "part", 1, 0, blue_title_block_parameter_part },
      { "provider", 1, 0, blue_title_block_parameter_provider },
      { "consumer", 1, 0, blue_title_block_parameter_consumer },
      { "revision", 1, 0, blue_title_block_parameter_revision },
      { "reference", 1, 0, blue_title_block_parameter_reference },
      { "page", 1, 0, blue_title_block_parameter_page },
      { "of", 1, 0, blue_title_block_parameter_of },
      { "time", 1, 0, blue_title_block_parameter_time },
      { "background-color-xml",
        1,
        0,
        blue_title_block_parameter_background_color_xml },
      { "line-color-xml", 1, 0, blue_title_block_parameter_line_color_xml },
      { "text-color-xml", 1, 0, blue_title_block_parameter_text_color_xml },
      { 0, 0, 0, 0 }
    };
  xmlDocPtr doc;
  color_s *color;

  if (!tb) tb = title_block_create();
  if (!tb) return NULL;

  blue_title_block_unset_changes();

  opterr = 0;
  optind = 1;
  while ((c = getopt_long(argc, argv, "vh", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case blue_title_block_parameter_title:
        title_block_set_title(tb, optarg);
        blue_title_block_set_change(blue_title_block_parameter_title);
        break;
      case blue_title_block_parameter_part:
        title_block_set_part(tb, optarg);
        blue_title_block_set_change(blue_title_block_parameter_part);
        break;
      case blue_title_block_parameter_provider:
        title_block_set_provider(tb, optarg);
        blue_title_block_set_change(blue_title_block_parameter_provider);
        break;
      case blue_title_block_parameter_consumer:
        title_block_set_consumer(tb, optarg);
        blue_title_block_set_change(blue_title_block_parameter_consumer);
        break;
      case blue_title_block_parameter_revision:
        title_block_set_revision(tb, optarg);
        blue_title_block_set_change(blue_title_block_parameter_revision);
        break;
      case blue_title_block_parameter_reference:
        title_block_set_reference(tb, optarg);
        blue_title_block_set_change(blue_title_block_parameter_reference);
        break;
      case blue_title_block_parameter_page:
        title_block_set_page(tb, strtol(optarg, NULL, 10));
        blue_title_block_set_change(blue_title_block_parameter_page);
        break;
      case blue_title_block_parameter_of:
        title_block_set_of(tb, strtol(optarg, NULL, 10));
        blue_title_block_set_change(blue_title_block_parameter_of);
        break;
      case blue_title_block_parameter_time:
        title_block_set_time(tb, convert_iso_8601(optarg));
        blue_title_block_set_change(blue_title_block_parameter_time);
        break;
      case blue_title_block_parameter_background_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          title_block_set_background_color(tb, color);
        blue_title_block_set_change(
          blue_title_block_parameter_background_color_xml);
        xmlFreeDoc(doc);
        break;
      case blue_title_block_parameter_line_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          title_block_set_line_color(tb, color);
        blue_title_block_set_change(blue_title_block_parameter_line_color_xml);
        xmlFreeDoc(doc);
        break;
      case blue_title_block_parameter_text_color_xml:
        doc = xmlReadFile(optarg, "UTF-8", 0);
        color = color_from_xml_doc(doc);
        if (color)
          title_block_set_text_color(tb, color);
        blue_title_block_set_change(blue_title_block_parameter_text_color_xml);
        break;
    }
  }

  blue_title_block_unset_changes();

  return tb;
}

int blue_title_block_check(title_block_s *tb)
{
  int i;

  assert(tb);

  unset_errors();

  for (i = blue_title_block_parameter_BEG;
       i < blue_title_block_parameter_END;
       i++)
    if (get_error(i))
      return 1;

  return 0;
}

void blue_title_block_check_error(void)
{
  if (get_error(blue_title_block_parameter_title))
    fprintf(stderr, "Parameter Error; title\n");
  if (get_error(blue_title_block_parameter_part))
    fprintf(stderr, "Parameter Error; part\n");
  if (get_error(blue_title_block_parameter_provider))
    fprintf(stderr, "Parameter Error; provider\n");
  if (get_error(blue_title_block_parameter_consumer))
    fprintf(stderr, "Parameter Error; consumer\n");
  if (get_error(blue_title_block_parameter_revision))
    fprintf(stderr, "Parameter Error; revision\n");
  if (get_error(blue_title_block_parameter_reference))
    fprintf(stderr, "Parameter Error; reference\n");
  if (get_error(blue_title_block_parameter_page))
    fprintf(stderr, "Parameter Error; page\n");
  if (get_error(blue_title_block_parameter_of))
    fprintf(stderr, "Parameter Error; of\n");
  if (get_error(blue_title_block_parameter_time))
    fprintf(stderr, "Parameter Error; time\n");
  if (get_error(blue_title_block_parameter_background_color_xml))
    fprintf(stderr, "Parameter Error; background-color-xml\n");
  if (get_error(blue_title_block_parameter_line_color_xml))
    fprintf(stderr, "Parameter Error; line-color-xml\n");
  if (get_error(blue_title_block_parameter_text_color_xml))
    fprintf(stderr, "Parameter Error; text-color-xml\n");
}

unsigned char blue_title_block_get_change(blue_title_block_parameter_t p)
{
  return changed[p - blue_title_block_parameter_BEG];
}

void blue_title_block_set_change(blue_title_block_parameter_t p)
{
  changed[p - blue_title_block_parameter_BEG] = 1;
}

void blue_title_block_unset_changes(void)
{
  memset(changed, 0, sizeof(changed));
}

static unsigned char get_error(blue_title_block_parameter_t p)
{
  return errors[p - blue_title_block_parameter_BEG];
}

/* Currently unused
static void set_error(blue_title_block_parameter_t p)
{
  errors[p - blue_title_block_parameter_BEG] = 1;
}
*/

static void unset_errors(void)
{
  memset(errors, 0, sizeof(errors));
}

static time_t convert_iso_8601(char *iso_8601_time)
{
  assert(iso_8601_time);
  struct tm tm;
  int len;
  int offset = 0;
  time_t tim;
  int dir = 0;

  strptime(optarg, "%Y-%m-%dT%H:%M:%S", &tm);
  tim = timegm(&tm);
  
  len = strlen(iso_8601_time);

  if (iso_8601_time[len-6] == '+')
    dir = -1;
  else if (iso_8601_time[len-6] == '-')
    dir = 1;

  if (dir)
  {
    offset = atoi(&iso_8601_time[len-4]) * 3600;
    offset += atoi(&iso_8601_time[len-2]) * 60;
    offset *= dir;
    tim += offset;
  }

  return tim;
}

