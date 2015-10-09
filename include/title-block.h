/*!
    @file title-block.h

    @brief HEADER_BRIEF

    @timestamp Fri, 09 Oct 2015 03:31:15 +0000

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

    @file title-block.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef TITLE_BLOCK_H
#define TITLE_BLOCK_H

#include <time.h>

#include "color.h"

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef struct
{
    /*! @brief ELEMENT_BRIEF */
  char title[31];
    /*! @brief ELEMENT_BRIEF */
  char part[31];
    /*! @brief ELEMENT_BRIEF */
  char provider[21];
    /*! @brief ELEMENT_BRIEF */
  char consumer[21];
    /*! @brief ELEMENT_BRIEF */
  char revision[11];
    /*! @brief ELEMENT_BRIEF */
  char reference[11];
    /*! @brief ELEMENT_BRIEF */
  int page;
    /*! @brief ELEMENT_BRIEF */
  int of;
    /*! @brief ELEMENT_BRIEF */
  time_t time;
    /*! @brief ELEMENT_BRIEF */
  color_s *background_color;
    /*! @brief ELEMENT_BRIEF */
  color_s *line_color;
    /*! @brief ELEMENT_BRIEF */
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
