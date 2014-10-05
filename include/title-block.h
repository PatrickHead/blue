#ifndef TITLE_BLOCK_H
#define TITLE_BLOCK_H

#include <time.h>

#include "color.h"

typedef struct
{
  char title[31];
  char part[31];
  char provider[21];
  char consumer[21];
  char revision[11];
  char reference[11];
  int page;
  int of;
  time_t time;
  color_s *background_color;
  color_s *line_color;
  color_s *text_color;
} title_block_s;

title_block_s *title_block_create(void);
void title_block_destroy(title_block_s *tb);
title_block_s *title_block_copy(title_block_s *tb);

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
                     color_s *text_color);
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
                     color_s **text_color);

void title_block_set_title(title_block_s *tb, char *s);
char *title_block_get_title(title_block_s *tb);

void title_block_set_part(title_block_s *tb, char *s);
char *title_block_get_part(title_block_s *tb);

void title_block_set_provider(title_block_s *tb, char *s);
char *title_block_get_provider(title_block_s *tb);

void title_block_set_consumer(title_block_s *tb, char *s);
char *title_block_get_consumer(title_block_s *tb);

void title_block_set_revision(title_block_s *tb, char *s);
char *title_block_get_revision(title_block_s *tb);

void title_block_set_reference(title_block_s *tb, char *s);
char *title_block_get_reference(title_block_s *tb);

void title_block_set_page(title_block_s *tb, int page);
int title_block_get_page(title_block_s *tb);

void title_block_set_of(title_block_s *tb, int of);
int title_block_get_of(title_block_s *tb);

void title_block_set_time(title_block_s *tb, time_t t);
time_t title_block_get_time(title_block_s *tb);

void title_block_set_background_color(title_block_s *tb, color_s *color);
color_s *title_block_get_background_color(title_block_s *tb);

void title_block_set_line_color(title_block_s *tb, color_s *color);
color_s *title_block_get_line_color(title_block_s *tb);

void title_block_set_text_color(title_block_s *tb, color_s *color);
color_s *title_block_get_text_color(title_block_s *tb);

#endif // TITLE_BLOCK_H
