#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "title-block.h"

title_block_s *title_block_create(void)
{
  title_block_s *tb;

  tb = (title_block_s *)malloc(sizeof(title_block_s));
  memset(tb, 0, sizeof(title_block_s));

  strcpy(tb->title, "TITLE");
  strcpy(tb->part, "PART");
  strcpy(tb->provider, "PROVIDER");
  strcpy(tb->consumer, "CONSUMER");
  strcpy(tb->revision, "REVISION");
  strcpy(tb->reference, "REFERENCE");
  tb->page = 1;
  tb->of = 1;
  tb->time = time(NULL);

  tb->background_color = color_create();
  color_set_tag(tb->background_color, "background-color");
  color_white(tb->background_color);

  tb->line_color = color_create();
  color_set_tag(tb->line_color, "line-color");
  color_black(tb->line_color);

  tb->text_color = color_create();
  color_set_tag(tb->text_color, "text-color");
  color_black(tb->text_color);

  return tb;
}

void title_block_destroy(title_block_s *tb)
{
  assert(tb);
  if (tb->background_color) color_destroy(tb->background_color);
  if (tb->line_color) color_destroy(tb->line_color);
  if (tb->text_color) color_destroy(tb->text_color);
  free(tb);
}

title_block_s *title_block_copy(title_block_s *tb)
{
  title_block_s *ntb;

  assert(tb);

  ntb = title_block_create();
  memcpy(ntb, tb, sizeof(title_block_s));

  if (tb->background_color)
    ntb->background_color = color_copy(tb->background_color);
  if (tb->line_color) ntb->line_color = color_copy(tb->line_color);
  if (tb->text_color) ntb->text_color = color_copy(tb->text_color);

  return ntb;
}

void title_block_set(title_block_s *tb,
                     char *title,
                     char *part,
                     char *provider,
                     char *consumer,
                     char *revision,
                     char *reference,
                     int page,
                     int of,
                     time_t time,
                     color_s *background_color,
                     color_s *line_color,
                     color_s *text_color)
{
  assert(tb);
  assert(title);
  assert(part);
  assert(provider);
  assert(consumer);
  assert(revision);
  assert(reference);
  assert(background_color);
  assert(line_color);
  assert(text_color);

  title_block_set_title(tb, title);
  title_block_set_part(tb, part);
  title_block_set_provider(tb, provider);
  title_block_set_consumer(tb, consumer);
  title_block_set_revision(tb, revision);
  title_block_set_reference(tb, reference);
  title_block_set_page(tb, page);
  title_block_set_of(tb, of);
  title_block_set_time(tb, time);
  title_block_set_background_color(tb, background_color);
  title_block_set_line_color(tb, line_color);
  title_block_set_text_color(tb, text_color);
}

void title_block_get(title_block_s *tb,
                     char **title,
                     char **part,
                     char **provider,
                     char **consumer,
                     char **revision,
                     char **reference,
                     int *page,
                     int *of,
                     time_t *time,
                     color_s **background_color,
                     color_s **line_color,
                     color_s **text_color)
{
  assert(tb);
  assert(title);
  assert(part);
  assert(provider);
  assert(consumer);
  assert(revision);
  assert(reference);
  assert(page);
  assert(of);
  assert(time);
  assert(background_color);
  assert(line_color);
  assert(text_color);

  *title = title_block_get_title(tb);
  *part = title_block_get_part(tb);
  *provider = title_block_get_provider(tb);
  *consumer = title_block_get_consumer(tb);
  *revision = title_block_get_revision(tb);
  *reference = title_block_get_reference(tb);
  *page = title_block_get_page(tb);
  *of = title_block_get_of(tb);
  *time = title_block_get_time(tb);
  *background_color = title_block_get_background_color(tb);
  *line_color = title_block_get_line_color(tb);
  *text_color = title_block_get_text_color(tb);
}

void title_block_set_title(title_block_s *tb, char *s)
{
  assert(tb);
  assert(s);
  strncpy(tb->title, s, 30);
}

char *title_block_get_title(title_block_s *tb)
{
  assert(tb);
  return tb->title;
}

void title_block_set_part(title_block_s *tb, char *s)
{
  assert(tb);
  assert(s);
  strncpy(tb->part, s, 30);
}

char *title_block_get_part(title_block_s *tb)
{
  assert(tb);
  return tb->part;
}

void title_block_set_provider(title_block_s *tb, char *s)
{
  assert(tb);
  assert(s);
  strncpy(tb->provider, s, 20);
}

char *title_block_get_provider(title_block_s *tb)
{
  assert(tb);
  return tb->provider;
}

void title_block_set_consumer(title_block_s *tb, char *s)
{
  assert(tb);
  assert(s);
  strncpy(tb->consumer, s, 20);
}

char *title_block_get_consumer(title_block_s *tb)
{
  assert(tb);
  return tb->consumer;
}

void title_block_set_revision(title_block_s *tb, char *s)
{
  assert(tb);
  assert(s);
  strncpy(tb->revision, s, 10);
}

char *title_block_get_revision(title_block_s *tb)
{
  assert(tb);
  return tb->revision;
}

void title_block_set_reference(title_block_s *tb, char *s)
{
  assert(tb);
  assert(s);
  strncpy(tb->reference, s, 10);
}

char *title_block_get_reference(title_block_s *tb)
{
  assert(tb);
  return tb->reference;
}

void title_block_set_page(title_block_s *tb, int page)
{
  assert(tb);
  tb->page = page;
}

int title_block_get_page(title_block_s *tb)
{
  assert(tb);
  return tb->page;
}

void title_block_set_of(title_block_s *tb, int of)
{
  assert(tb);
  tb->of = of;
}

int title_block_get_of(title_block_s *tb)
{
  assert(tb);
  return tb->of;
}

void title_block_set_time(title_block_s *tb, time_t t)
{
  assert(tb);
  tb->time = t;
}

time_t title_block_get_time(title_block_s *tb)
{
  assert(tb);
  return tb->time;
}

void title_block_set_background_color(title_block_s *tb, color_s *color)
{
  assert(tb);
  assert(color);
  if (tb->background_color) color_destroy(tb->background_color);
  tb->background_color = color;
  color_set_tag(tb->background_color, "background-color");
}

color_s *title_block_get_background_color(title_block_s *tb)
{
  assert(tb);
  return tb->background_color;
}

void title_block_set_line_color(title_block_s *tb, color_s *color)
{
  assert(tb);
  assert(color);
  if (tb->line_color) color_destroy(tb->line_color);
  tb->line_color = color;
  color_set_tag(tb->line_color, "line-color");
}

color_s *title_block_get_line_color(title_block_s *tb)
{
  assert(tb);
  return tb->line_color;
}

void title_block_set_text_color(title_block_s *tb, color_s *color)
{
  assert(tb);
  assert(color);
  if (tb->text_color) color_destroy(tb->text_color);
  tb->text_color = color;
  color_set_tag(tb->text_color, "text-color");
}

color_s *title_block_get_text_color(title_block_s *tb)
{
  assert(tb);
  return tb->text_color;
}

