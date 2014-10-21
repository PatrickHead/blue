/*!
    @file render-2d-cairo.c

    @brief SOURCE_BRIEF

    @timestamp Mon, 06 Jan 2014 15:17:36 +0000

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

    @file render-2d-cairo.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif // M_PI
#include <assert.h>
#include <pango/pangocairo.h>

  // Project related headers

#include "render-2d-cairo.h"

static void render_paper(cairo_surface_t *sur, drawing_s *d);
static void render_border(cairo_surface_t *sur, drawing_s *d);
static void render_title_block(cairo_surface_t *sur, drawing_s *d);
static void render_design(cairo_surface_t *sur, drawing_s *d);
static void render_design_layer(cairo_surface_t *sur, design_layer_s *d);
static void render_design_element(cairo_surface_t *sur, design_element_s *e);
static void render_design_element_dimension(cairo_surface_t *sur,
                                            design_element_s *e);
static void render_dimension_linear(cairo_surface_t *sur, design_element_s *e);
static void render_dimension_angular(cairo_surface_t *sur, design_element_s *e);
static void render_dimension_radial(cairo_surface_t *sur, design_element_s *e);
static void render_design_element_elliptic(cairo_surface_t *sur,
                                           design_element_s *e);
static void render_design_element_line(cairo_surface_t *sur, design_element_s *e); static void render_design_element_point(cairo_surface_t *sur,
                                          design_element_s *e);
static void render_design_element_polyline(cairo_surface_t *sur,
                                           design_element_s *e);
static void render_design_element_spline(cairo_surface_t *sur,
                                         design_element_s *e);
static void render_design_element_text(cairo_surface_t *sur,
                                       design_element_s *e);
static void render_design_element_tolerance(cairo_surface_t *sur,
                                            design_element_s *e);

static double convert_to_points(double dim, units_t ut);
static cairo_rectangle_t paper_size(paper_s *p);
static void set_design_scale(double scale);
static double get_design_scale(void);
static double scale(double coord, units_t units);
static vertex_s *adjust_vertex(vertex_s *v, double a, double d);
static double flip_y(cairo_surface_t *sur, double y);
static void translate_coords(vertex_s *v);
static void untranslate_coords(vertex_s *v);
static void scale_coords(vertex_s *v, units_t units);
static void set_x_translation(double x);
static double get_x_translation(void);
static void set_y_translation(double y);
static double get_y_translation(void);
static void set_text_extents(cairo_text_extents_t tx);
static cairo_text_extents_t get_text_extents(void);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *endpoint(vertex_s *pt, double a, double l);
static void set_design_units(units_t units);
static units_t get_design_units(void);
static void set_design_line_styles(design_s *d);
static design_line_styles_s *get_design_line_styles(void);
static void set_design_fill_styles(design_s *d);
static design_fill_styles_s *get_design_fill_styles(void);
static void set_line_style(cairo_t *ctx, char *style);
static void unset_line_style(cairo_t *ctx);
static void close_path(cairo_t *ctx, design_element_s *e);
static void fill(cairo_t *ctx, design_element_s *e);
static void fill_lhs(cairo_t *ctx, design_fill_style_s *fs);
static void fill_image(cairo_t *ctx, design_fill_style_s *fs);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void pattern_destroy(cairo_pattern_t *pattern);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

cairo_surface_t *render_2d_cairo(drawing_s *d)
{
  cairo_surface_t *paper_surface;
  cairo_rectangle_t paper_rect;

    // Sanity check parameters.
  assert(d);

  paper_rect = paper_size(d->paper);

  paper_surface =
    cairo_recording_surface_create(CAIRO_CONTENT_COLOR, &paper_rect);

  render_paper(paper_surface, d);

    // Return RETVAL
  return paper_surface;
}

static void render_paper(cairo_surface_t *sur, drawing_s *d)
{
  cairo_t *ctx;
  cairo_rectangle_t rect;
  double x, y, width, height;
  cairo_surface_t *border_surface;

    // Sanity check parameters.
  assert(sur);
  assert(d);

  ctx = cairo_create(sur);
  
  cairo_recording_surface_get_extents(sur, &rect);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_rectangle(ctx, 0.0, 0.0, rect.width, rect.height);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgb(ctx, 1.0, 1.0, 1.0);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_fill(ctx);

  cairo_destroy(ctx);

  x = d->paper->margins->left;
  y = d->paper->margins->top;
  width = d->paper->width - (d->paper->margins->left
                             + d->paper->margins->right);
  height = d->paper->height
           - (d->paper->margins->top
              + d->paper->margins->bottom);
  x = convert_to_points(x, d->paper->margins->units);
  y = convert_to_points(y, d->paper->margins->units);
  width = convert_to_points(width, d->paper->margins->units);
  height = convert_to_points(height, d->paper->margins->units);

  border_surface = cairo_surface_create_for_rectangle(sur, x, y, width, height);
  render_border(border_surface, d);
  cairo_surface_destroy(border_surface);
}

static void render_border(cairo_surface_t *sur, drawing_s *d)
{
  cairo_t *ctx;
  cairo_rectangle_t rect;
  double x, y, width, height;
  cairo_surface_t *title_block_surface;
  cairo_surface_t *design_surface;

    // Sanity check parameters.
  assert(sur);

  get_surface_size(sur, &rect);

  ctx = cairo_create(sur);
  
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_rectangle(ctx, 0.0, 0.0, rect.width, rect.height);
  cairo_set_line_width(ctx, 3.6);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgb(ctx, 0.85, 0.85, 0.85); // medium grey
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_stroke(ctx);

  cairo_destroy(ctx);

    // size title block
  x = 0.0;
  y = rect.height - 36.0;
  width = rect.width;
  height = 36.0;

  title_block_surface =
    cairo_surface_create_for_rectangle(sur, x, y, width, height);
  render_title_block(title_block_surface, d);
  cairo_surface_destroy(title_block_surface);

    // size design area
  x = convert_to_points(d->border->margins->left, d->border->margins->units);
  y = convert_to_points(d->border->margins->top, d->border->margins->units);
  width = rect.width
          - convert_to_points(d->border->margins->left
                                + d->border->margins->right,
                              d->border->margins->units);
  height = (rect.height - 36.0)
           - convert_to_points(d->border->margins->top
                                 + d->border->margins->bottom,
                               d->border->margins->units);

  design_surface = cairo_surface_create_for_rectangle(sur, x, y, width, height);
  render_design(design_surface, d);
  cairo_surface_destroy(design_surface);
}

static void render_title_block(cairo_surface_t *sur, drawing_s *d)
{
  cairo_t *ctx;
  cairo_rectangle_t rect;
  PangoLayout *layout;
  PangoFontDescription *desc;
  char buf[40];

    // Sanity check parameters.
  assert(sur);

  ctx = cairo_create(sur);
  
  get_surface_size(sur, &rect);

    // Default source settings
  cairo_set_line_width(ctx, 1.8);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgb(ctx, 0.85, 0.85, 0.85); // medium grey

    // Basic Box
    // Note:  Only half the line width will display, as this is on the outside
    //        of the clipping region
  cairo_save(ctx);
  cairo_set_line_width(ctx, 3.6);
  /* free the layout object */
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_rectangle(ctx, 0.0, 0.0, rect.width, rect.height);
  cairo_stroke(ctx);
  cairo_restore(ctx);

    // Horizontal Divider
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_move_to(ctx, 0.0, rect.height / 2.0);
  cairo_line_to(ctx, rect.width, rect.height / 2.0);
  cairo_stroke(ctx);

    // Vertical Dividers
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_move_to(ctx, rect.width * (5.0/14.0), rect.height);
  cairo_line_to(ctx, rect.width * (5.0/14.0), 0.0);
  cairo_stroke(ctx);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_move_to(ctx, rect.width * (4.0/7.0), rect.height);
  cairo_line_to(ctx, rect.width * (4.0/7.0), 0.0);
  cairo_stroke(ctx);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_move_to(ctx, rect.width * (6.0/7.0), rect.height);
  cairo_line_to(ctx, rect.width * (6.0/7.0), 0.0);
  cairo_stroke(ctx);

    // Title block data

      // Set common text settings
  layout = pango_cairo_create_layout(ctx);
  desc = pango_font_description_from_string("MonoSpace 8");
  pango_layout_set_font_description(layout, desc);
  pango_font_description_free(desc);
  cairo_set_source_rgb(ctx, 0.0, 0.0, 0.0);

      // Title
  pango_layout_set_text(layout, d->title_block->title, -1);
  cairo_move_to(ctx, 6.0, 3.0);
  pango_cairo_show_layout(ctx, layout);

      // Part
  pango_layout_set_text(layout, d->title_block->part, -1);
  cairo_move_to(ctx, 6.0, (rect.height / 2.0) + 3.0);
  pango_cairo_show_layout(ctx, layout);

      // Reference
  snprintf(buf, 14, "ref %s", d->title_block->reference);
  pango_layout_set_text(layout, buf, -1);
  cairo_move_to(ctx, (rect.width * 5.0 / 14.0) + 6.0, 3.0);
  pango_cairo_show_layout(ctx, layout);

      // Revision
  snprintf(buf, 14, "rev %s", d->title_block->revision);
  pango_layout_set_text(layout, buf, -1);
  cairo_move_to(ctx, (rect.width * 5.0 / 14.0) + 6.0, (rect.height / 2.0) + 3.0);
  pango_cairo_show_layout(ctx, layout);

      // Provider
  snprintf(buf, 24, " by %s", d->title_block->provider);
  pango_layout_set_text(layout, buf, -1);
  cairo_move_to(ctx, (rect.width * 4.0 / 7.0) + 6.0, 3.0);
  pango_cairo_show_layout(ctx, layout);

      // Consumer
  snprintf(buf, 24, "for %s", d->title_block->consumer);
  pango_layout_set_text(layout, buf, -1);
  cairo_move_to(ctx, (rect.width * 4.0 / 7.0) + 6.0, (rect.height / 2.0) + 3.0);
  pango_cairo_show_layout(ctx, layout);

      // Date
  strftime(buf, 11, "%Y-%m-%d", localtime(&d->title_block->time));
  pango_layout_set_text(layout, buf, -1);
  cairo_move_to(ctx, (rect.width * 6.0 / 7.0) + 6.0, 3.0);
  pango_cairo_show_layout(ctx, layout);

      // Page
  snprintf(buf, 12, "pg %d/%d", d->title_block->page, d->title_block->of);
  pango_layout_set_text(layout, buf, -1);
  cairo_move_to(ctx, (rect.width * 6.0 / 7.0) + 6.0, (rect.height / 2.0) + 3.0);
  pango_cairo_show_layout(ctx, layout);

    // Free up the layout object
  g_object_unref (layout);

  cairo_destroy(ctx);
}

static void render_design(cairo_surface_t *sur, drawing_s *d)
{
  design_layer_s *layer;
  cairo_surface_t *unbounded;
  cairo_surface_t *bounded;
  cairo_t *ctx;
  cairo_rectangle_t unbounded_ext;
  cairo_rectangle_t bounded_ext;
  cairo_rectangle_t surface_ext;
  double scale_factor;
  double x_scale;
  double y_scale;

    // Sanity check parameters.
  assert(sur);
  assert(d);

  if (!d->design) return;
  if (d->design->defaults)
    set_design_units(design_defaults_get_units(d->design->defaults));
  set_design_line_styles(d->design);
  set_design_fill_styles(d->design);

    // Find the extents of the design drawing

  unbounded = cairo_recording_surface_create(CAIRO_CONTENT_COLOR, NULL);

  if (d->design->layers)
  {
    for (layer = (design_layer_s *)list_head(d->design->layers->layers);
         layer;
         layer = (design_layer_s *)list_next(d->design->layers->layers))
    {
      if (design_layer_get_visibility(layer) == design_visibility_type_visible)
        render_design_layer(unbounded, layer);
    }
  }

  cairo_recording_surface_ink_extents(unbounded,
                                      &unbounded_ext.x,
                                      &unbounded_ext.y,
                                      &unbounded_ext.width,
                                      &unbounded_ext.height);

  set_x_translation(unbounded_ext.x);
  set_y_translation(unbounded_ext.y);

    // adjust extents to origin
  unbounded_ext.x = unbounded_ext.y = 0.0;

  cairo_surface_destroy(unbounded);

    // Calculate scaling factor

  get_surface_size(sur, &surface_ext);

  x_scale = surface_ext.width / unbounded_ext.width;
  y_scale = surface_ext.height / unbounded_ext.height;
  scale_factor = fmin(x_scale, y_scale);

  set_design_scale(scale_factor);

  bounded_ext.x = unbounded_ext.x * get_design_scale();
  bounded_ext.y = unbounded_ext.y * get_design_scale();
  bounded_ext.width = unbounded_ext.width * get_design_scale();
  bounded_ext.height = unbounded_ext.height * get_design_scale();

    // Make the drawing on the bounded surface

  bounded = cairo_recording_surface_create(CAIRO_CONTENT_COLOR, &bounded_ext);
  get_surface_size(bounded, &bounded_ext); // to catch cairo adjustments

  ctx = cairo_create(bounded);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_rectangle(ctx, 0.0, 0.0, bounded_ext.width, bounded_ext.height);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgb(ctx, 1.0, 1.0, 1.0);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_fill(ctx);
  cairo_destroy(ctx);

  if (d->design->layers)
  {
    for (layer = (design_layer_s *)list_head(d->design->layers->layers);
         layer;
         layer = (design_layer_s *)list_next(d->design->layers->layers))
    {
      if (design_layer_get_visibility(layer) == design_visibility_type_visible)
        render_design_layer(bounded, layer);
    }
  }

    // Transfer the bounded drawing to the paper's surface

  ctx = cairo_create(sur);
  cairo_translate(ctx,
                  (surface_ext.width - bounded_ext.width) / 2.0,
                  (surface_ext.height - bounded_ext.height) / 2.0);
  cairo_set_source_surface(ctx, bounded, 0.0, 0.0);
  cairo_paint(ctx);
  cairo_destroy(ctx);

  cairo_surface_destroy(bounded);
}

static void render_design_layer(cairo_surface_t *sur, design_layer_s *l)
{
  design_element_s *element;

    // Sanity check parameters.
  assert(sur);
  assert(l);

  if (l->elements)
  {
    for (element = (design_element_s *)list_head(l->elements->elements);
         element;
         element = (design_element_s *)list_next(l->elements->elements))
      render_design_element(sur, element);
  }
}

static void render_design_element(cairo_surface_t *sur, design_element_s *e)
{
  switch (e->type)
  {
    case design_element_type_dimension:
      render_design_element_dimension(sur, e);
      break;
    case design_element_type_elliptic:
      render_design_element_elliptic(sur, e);
      break;
    case design_element_type_line:
      render_design_element_line(sur, e);
      break;
    case design_element_type_point:
      render_design_element_point(sur, e);
      break;
    case design_element_type_polyline:
      render_design_element_polyline(sur, e);
      break;
    case design_element_type_spline:
      render_design_element_spline(sur, e);
      break;
    case design_element_type_text:
      render_design_element_text(sur, e);
      break;
    case design_element_type_tolerance:
      render_design_element_tolerance(sur, e);
      break;
    default: break;
  }
}

static void render_design_element_dimension(cairo_surface_t *sur,
                                            design_element_s *e)
{
    // Sanity check parameters.
  assert(sur);

  switch (e->type)
  {
    case design_element_type_dimension:
      switch (design_dimension_get_type(e->dimension))
      {
        case design_dimension_type_linear:
          render_dimension_linear(sur, e);
          break;
        case design_dimension_type_angular:
          render_dimension_angular(sur, e);
          break;
        case design_dimension_type_radial:
          render_dimension_radial(sur, e);
          break;
        default: break;
      }
      break;
    default: break;
  }
}

static void render_dimension_linear(cairo_surface_t *sur, design_element_s *e)
{
  cairo_t *ctx;
  vertex_s *start;
  vertex_s *end;
  double rise, run, angle;
  vertex_s *dimline_start;
  vertex_s *dimline_end;
  vertex_s *dimline_u1;
  vertex_s *dimline_u2;
  vertex_s *extline_start;
  vertex_s *extline_end;
  vertex_s *text_point;
  double gap;
  double above;
  double below;
  double length;
  double dimline_length;
  double open_length;
  char dimstr[40];
  design_element_s *el;
  design_dimension_s *dim;
  design_linear_s *lin;
  color_s *clr;
  cairo_text_extents_t text_ext;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (!clr) return;

  dim = e->dimension;
  if (!dim) return;

  lin = design_dimension_get_linear(dim);
  if (!lin) return;

  length = sqrt(pow(design_linear_get_end(lin)->x
                    - design_linear_get_start(lin)->x, 2.0)
                + pow(design_linear_get_end(lin)->y
                      - design_linear_get_start(lin)->y, 2.0));

    // generate some automatic parameters, if needed.

  if (!design_linear_get_gap(lin))
    design_linear_set_gap(lin, length * 0.15);
  if (!design_linear_get_extension_above(lin))
    design_linear_set_extension_above(lin, design_linear_get_gap(lin) * 0.25);
  if (!design_linear_get_extension_below(lin))
    design_linear_set_extension_below(lin, design_linear_get_gap(lin) * 0.75);
  if (!design_dimension_get_text_size(dim))
    design_dimension_set_text_size(dim, length * 0.05);

  if (design_linear_get_dimension(lin))
    length = design_linear_get_dimension(lin);

  sprintf(dimstr, "%.*f %s",
            design_dimension_get_precision(dim),
            length,
            units2str(design_element_get_units(e)));

  ctx = cairo_create(sur);

  set_line_style(ctx, e->line_style);
  cairo_set_line_width(ctx, design_element_get_line_weight(e));
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a);

  gap = scale(design_linear_get_gap(lin), design_element_get_units(e));
  above = scale(design_linear_get_extension_above(lin),
                design_element_get_units(e));
  below = scale(design_linear_get_extension_below(lin),
                design_element_get_units(e));

  start = design_linear_get_start(lin);
  translate_coords(start);
  start->x = scale(start->x, design_element_get_units(e));
  start->y = scale(start->y, design_element_get_units(e));
  end = design_linear_get_end(lin);
  translate_coords(end);
  end->x = scale(end->x, design_element_get_units(e));
  end->y = scale(end->y, design_element_get_units(e));

  rise = (end->y - start->y);
  run = (end->x - start->x);
  angle = run ? atan(rise/run) : M_PI / 2.0;

    // Main dimension line

  dimline_start = adjust_vertex(start, angle, gap);
  dimline_end = adjust_vertex(end, angle, gap);

    // Start with dimension text, so we can get its size for dim line segments

    // location of text is center point on dimension line
    // we also have to "undo" scaling and translation, because
    // render_design_element_text will also scale and translate
  text_point = vertex_create();
  text_point->x = ((dimline_start->x + dimline_end->x) / 2.0) / get_design_scale();
  text_point->y = ((dimline_start->y + dimline_end->y) / 2.0) / get_design_scale();
  text_point->x += get_x_translation();
  text_point->y += get_y_translation();

  el = design_element_create();

  design_element_set_type(el, design_element_type_text);
  design_text_set_type(el->text, design_text_type_drawing);
  design_text_set_location(el->text, text_point);
  design_text_set_anchor_point(el->text, design_anchor_location_type_center);
  design_text_set_size(el->text, design_dimension_get_text_size(dim));
  design_text_set_text(el->text, dimstr);

  render_design_element_text(sur, el);

  text_ext = get_text_extents();

  dimline_length = sqrt(pow(dimline_end->x
                            - dimline_start->x, 2.0)
                        + pow(dimline_end->y
                              - dimline_start->y, 2.0));
  open_length = text_ext.width + text_ext.height;
  dimline_u1 =
      endpoint(dimline_start, angle, (dimline_length - open_length) / 2.0);
  dimline_u2 =
      endpoint(dimline_u1, angle, open_length);

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a * 0.80);

    // Dimension line segments
  cairo_move_to(ctx, dimline_start->x, flip_y(sur, dimline_start->y));
  cairo_line_to(ctx, dimline_u1->x, flip_y(sur, dimline_u1->y));
  cairo_stroke(ctx);
  cairo_move_to(ctx, dimline_u2->x, flip_y(sur, dimline_u2->y));
  cairo_line_to(ctx, dimline_end->x, flip_y(sur, dimline_end->y));
  cairo_stroke(ctx);

    // Dimension line arrows

  dimline_u1 = endpoint(dimline_start,
                        angle - (30.0*M_PI / 180.0),
                        text_ext.height / 1.5);
  dimline_u2 = endpoint(dimline_start,
                        angle + (30.0*M_PI / 180.0),
                        text_ext.height / 1.5);
  cairo_move_to(ctx, dimline_start->x, flip_y(sur, dimline_start->y));
  cairo_line_to(ctx, dimline_u1->x, flip_y(sur, dimline_u1->y));
  cairo_line_to(ctx, dimline_u2->x, flip_y(sur, dimline_u2->y));
  cairo_close_path(ctx);
  cairo_fill(ctx);
  cairo_stroke(ctx);

  dimline_u1 = endpoint(dimline_end,
                        angle - (30 * M_PI / 180.0),
                        -text_ext.height / 1.5);
  dimline_u2 = endpoint(dimline_end,
                        angle + (30 * M_PI / 180.0),
                        -text_ext.height / 1.5);
  cairo_move_to(ctx, dimline_end->x, flip_y(sur, dimline_end->y));
  cairo_line_to(ctx, dimline_u1->x, flip_y(sur, dimline_u1->y));
  cairo_line_to(ctx, dimline_u2->x, flip_y(sur, dimline_u2->y));
  cairo_close_path(ctx);
  cairo_fill(ctx);
  cairo_stroke(ctx);

    // Extensions lines
  if (gap >= 0)
  {
    extline_start = adjust_vertex(dimline_start, angle - M_PI, below);
    extline_end = adjust_vertex(dimline_start, angle, above);
  }
  else
  {
    extline_start = adjust_vertex(dimline_start, angle - M_PI, above);
    extline_end = adjust_vertex(dimline_start, angle, below);
  }

  cairo_move_to(ctx, extline_start->x, flip_y(sur, extline_start->y));
  cairo_line_to(ctx, extline_end->x, flip_y(sur, extline_end->y));
  cairo_stroke(ctx);

  if (gap >= 0)
  {
    extline_start = adjust_vertex(dimline_end, angle - M_PI, below);
    extline_end = adjust_vertex(dimline_end, angle, above);
  }
  else
  {
    extline_start = adjust_vertex(dimline_end, angle - M_PI, above);
    extline_end = adjust_vertex(dimline_end, angle, below);
  }

  cairo_move_to(ctx, extline_start->x, flip_y(sur, extline_start->y));
  cairo_line_to(ctx, extline_end->x, flip_y(sur, extline_end->y));
  cairo_stroke(ctx);

  design_element_destroy(el);

  cairo_destroy(ctx);
}

static void render_dimension_angular(cairo_surface_t *sur, design_element_s *e)
{
  cairo_t *ctx;
  double line1_base;
  double line2_base;
  double line1_angle;
  double line2_angle;
  double line1_x_component;
  double line1_y_component;
  double line2_x_component;
  double line2_y_component;
  double marker_radius;
  vertex_s *line1_start;
  vertex_s *line1_end;
  vertex_s *line2_start;
  vertex_s *line2_end;
  double marker1_angle;
  double marker2_angle;
  double text_angle;
  vertex_s *text_point;
  vertex_s *arrow1_head;
  vertex_s *arrow1_tail1;
  vertex_s *arrow1_tail2;
  vertex_s *arrow2_head;
  vertex_s *arrow2_tail1;
  vertex_s *arrow2_tail2;
  char text[40];
  design_element_s *el;
  design_dimension_s *dim;
  design_angular_s *ang;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (!clr) return;

  dim = e->dimension;
  if (!dim) return;

  ang = design_dimension_get_angular(dim);
  if (!ang) return;

  ctx = cairo_create(sur);

  line1_base = sqrt(pow(design_angular_get_beta(ang)->x
                        - design_angular_get_alpha(ang)->x, 2.0)
                    + pow(design_angular_get_beta(ang)->y
                          - design_angular_get_alpha(ang)->y, 2.0));
  line2_base = sqrt(pow(design_angular_get_gamma(ang)->x
                        - design_angular_get_alpha(ang)->x, 2.0)
                    + pow(design_angular_get_gamma(ang)->y
                          - design_angular_get_alpha(ang)->y, 2.0));

    // calculate some automatic parameters
  if (!design_dimension_get_text_size(dim))
    design_dimension_set_text_size(dim, fmax(line1_base, line2_base) * 0.05);

    // translate basic parameters
  translate_coords(ang->alpha);
  translate_coords(ang->beta);
  translate_coords(ang->gamma);

  line1_x_component = design_angular_get_beta(ang)->x
                      - design_angular_get_alpha(ang)->x;
  line1_y_component = design_angular_get_beta(ang)->y
                      - design_angular_get_alpha(ang)->y;
  line2_x_component = design_angular_get_gamma(ang)->x
                      - design_angular_get_alpha(ang)->x;
  line2_y_component = design_angular_get_gamma(ang)->y
                      - design_angular_get_alpha(ang)->y;

  line1_angle = atan(line1_y_component / line1_x_component);
  line2_angle = atan(line2_y_component / line2_x_component);

  if ((line1_x_component < 0.0) && (line1_y_component >= 0.0))
    line1_angle = M_PI + line1_angle;
  else if ((line1_x_component < 0.0) && (line1_y_component < 0.0))
    line1_angle += M_PI;
  else if ((line1_x_component >= 0.0) && (line1_y_component < 0.0))
    line1_angle = (M_PI * 2.0) + line1_angle;

  if ((line2_x_component < 0.0) && (line2_y_component >= 0.0))
    line2_angle = M_PI + line2_angle;
  else if ((line2_x_component < 0.0) && (line2_y_component < 0.0))
    line2_angle += M_PI;
  else if ((line2_x_component >= 0.0) && (line2_y_component < 0.0))
    line2_angle = (M_PI * 2.0) + line2_angle;

  line1_start = endpoint(design_angular_get_beta(ang),
                         line1_angle,
                         design_angular_get_gap(ang));
  line1_end = endpoint(line1_start,
                       line1_angle,
                       design_angular_get_extension(ang));

  line2_start = endpoint(design_angular_get_gamma(ang),
                         line2_angle,
                         design_angular_get_gap(ang));
  line2_end = endpoint(line2_start,
                       line2_angle,
                       design_angular_get_extension(ang));

  marker_radius = ((line1_base + line2_base) / 2.0)
                  + design_angular_get_gap(ang);
  marker_radius += design_angular_get_extension(ang) * 0.5;

    // calculate marker stop angles
  marker1_angle = line1_angle + (10 * M_PI / 180.0); // + 10 degrees
  marker2_angle = line2_angle - (10 * M_PI / 180.0); // - 10 degrees

    // calculate angle for text center point
  text_angle = (line1_angle + line2_angle) / 2.0;
  if (line1_angle < line2_angle)
    text_angle -= M_PI;
  text_point = endpoint(design_angular_get_alpha(ang),
                        text_angle,
                        marker_radius);
  untranslate_coords(text_point);

    // prepare text string
  if (!design_angular_get_angle(ang))
  {
    if (line1_angle < line2_angle)
      design_angular_set_angle(ang, (line1_angle + (2.0 * M_PI)) - line2_angle);
    else
      design_angular_set_angle(ang, line1_angle - line2_angle);
  }
  sprintf(text, "%.*f\u00b0",
                design_dimension_get_precision(dim),
                design_angular_get_angle(ang) * 180.0 / M_PI);

    // calculate arrow points
  arrow1_head = endpoint(design_angular_get_alpha(ang),
                         line1_angle,
                         marker_radius);
  arrow1_tail1 = endpoint(arrow1_head,
                          line1_angle + (M_PI/2.0) - (30.0*M_PI / 180.0),
                          design_dimension_get_text_size(dim) / 1.5);
  arrow1_tail2 = endpoint(arrow1_head,
                          line1_angle + (M_PI/2.0) + (30.0*M_PI / 180.0),
                          design_dimension_get_text_size(dim) / 1.5);
  arrow2_head = endpoint(design_angular_get_alpha(ang),
                         line2_angle,
                         marker_radius);
  arrow2_tail1 = endpoint(arrow2_head,
                          line2_angle - (M_PI/2.0) - (30.0*M_PI / 180.0),
                          design_dimension_get_text_size(dim) / 1.5);
  arrow2_tail2 = endpoint(arrow2_head,
                          line2_angle - (M_PI/2.0) + (30.0*M_PI / 180.0),
                          design_dimension_get_text_size(dim) / 1.5);

  scale_coords(ang->alpha, design_element_get_units(e));
  scale_coords(ang->beta, design_element_get_units(e));
  scale_coords(ang->gamma, design_element_get_units(e));
  scale_coords(line1_start, design_element_get_units(e));
  scale_coords(line1_end, design_element_get_units(e));
  scale_coords(line2_start, design_element_get_units(e));
  scale_coords(line2_end, design_element_get_units(e));
  scale_coords(arrow1_head, design_element_get_units(e));
  scale_coords(arrow1_tail1, design_element_get_units(e));
  scale_coords(arrow1_tail2, design_element_get_units(e));
  scale_coords(arrow2_head, design_element_get_units(e));
  scale_coords(arrow2_tail1, design_element_get_units(e));
  scale_coords(arrow2_tail2, design_element_get_units(e));

  marker_radius = scale(marker_radius, design_element_get_units(e));

  set_line_style(ctx, e->line_style);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a * 0.80);

    // render extension lines
  cairo_move_to(ctx, line1_start->x, flip_y(sur, line1_start->y));
  //cairo_move_to(ctx, a.alpha.x, flip_y(sur, a.alpha.y));
  cairo_line_to(ctx, line1_end->x, flip_y(sur, line1_end->y));
  cairo_stroke(ctx);

  cairo_move_to(ctx, line2_start->x, flip_y(sur, line2_start->y));
  //cairo_move_to(ctx, a.alpha.x, flip_y(sur, a.alpha.y));
  cairo_line_to(ctx, line2_end->x, flip_y(sur, line2_end->y));
  cairo_stroke(ctx);

    // render marker arcs
  cairo_save(ctx);
  cairo_translate(ctx,
                  design_angular_get_alpha(ang)->x,
                  flip_y(sur, design_angular_get_alpha(ang)->y));
  cairo_scale(ctx, 1.0, -1.0);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

#warning render_dimension_angular(): following line causes cairo extent hiccup
  cairo_arc(ctx, 0.0, 0.0,
            marker_radius,
            fmin(line1_angle, marker1_angle),
            fmax(line1_angle, marker1_angle));
  cairo_stroke(ctx);
  cairo_arc(ctx, 0.0, 0.0,
            marker_radius,
            fmin(line2_angle, marker2_angle),
            fmax(line2_angle, marker2_angle));
  cairo_stroke(ctx);
  cairo_restore(ctx);

    // render arrow heads
  cairo_save(ctx);
  cairo_move_to(ctx, arrow1_head->x, flip_y(sur, arrow1_head->y));
  cairo_line_to(ctx, arrow1_tail1->x, flip_y(sur, arrow1_tail1->y));
  cairo_line_to(ctx, arrow1_tail2->x, flip_y(sur, arrow1_tail2->y));
  cairo_close_path(ctx);
  cairo_fill(ctx);
  cairo_stroke(ctx);
  cairo_move_to(ctx, arrow2_head->x, flip_y(sur, arrow2_head->y));
  cairo_line_to(ctx, arrow2_tail1->x, flip_y(sur, arrow2_tail1->y));
  cairo_line_to(ctx, arrow2_tail2->x, flip_y(sur, arrow2_tail2->y));
  cairo_close_path(ctx);
  cairo_fill(ctx);
  cairo_stroke(ctx);
  cairo_restore(ctx);

  cairo_destroy(ctx);

    // render text
  el = design_element_create();
  design_element_set_type(el, design_element_type_text);
  design_text_set_type(el->text, design_text_type_drawing);
  design_text_set_location(el->text, text_point);
  design_text_set_anchor_point(el->text, design_anchor_location_type_center);
  design_text_set_size(el->text, design_dimension_get_text_size(dim));
  design_text_set_text(el->text, text);
  render_design_element_text(sur, el);
  design_element_destroy(el);
}

static void render_dimension_radial(cairo_surface_t *sur, design_element_s *e)
{
  cairo_t *ctx;
  vertex_s *leader_start;
  vertex_s *leader_end;
  vertex_s *leader_ext_end;
  vertex_s *arrow_head;
  vertex_s *arrow_tail1;
  vertex_s *arrow_tail2;
  vertex_s *major_point;
  vertex_s *minor_point;
  double angle;
  double ext_side;
  double ext_length;
  double text_width;
  char text_major[40];
  char text_minor[40];
  cairo_text_extents_t major_extents;
  cairo_text_extents_t minor_extents;
  design_element_s *el;
  design_dimension_s *dim;
  design_radial_s *rad;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (!clr) return;

  dim = e->dimension;
  if (!dim) return;

  rad = design_dimension_get_radial(dim);
  if (!rad) return;

  memset(&major_extents, 0, sizeof(cairo_text_extents_t));
  memset(&minor_extents, 0, sizeof(cairo_text_extents_t));

  ctx = cairo_create(sur);

    // convert degrees to radians
  angle = design_radial_get_angle(rad) * M_PI / 180.0;
  if ((angle <= (M_PI / 2.0)) || (angle > (M_PI * 1.5)))
    ext_side = 1.0;
  else
    ext_side = -1.0;

    // leader always starts to center of elliptic

  leader_start = design_radial_get_center(rad);
  translate_coords(leader_start);

    // calculate key vertices
  ext_length = ext_side * design_dimension_get_text_size(dim) * 2.0;

  leader_end = endpoint(leader_start,
                        angle,
                        design_radial_get_major(rad)
                          + design_radial_get_leader(rad));
  leader_ext_end = endpoint(leader_end, 0, ext_length);
  arrow_head = leader_start;
  arrow_tail1 = endpoint(arrow_head,
                         angle + (12.5*M_PI / 180.0),
                         design_dimension_get_text_size(dim));
  arrow_tail2 = endpoint(arrow_head,
                         angle - (12.5*M_PI / 180.0),
                         design_dimension_get_text_size(dim));

    // prepare text
  cairo_set_font_size(ctx, design_dimension_get_text_size(dim));

  switch (design_dimension_get_type(dim))
  {
    case design_radial_type_radius:
      if (design_radial_get_minor(rad))
      {
        sprintf(text_major, "MR%.*f",
                            design_dimension_get_precision(dim),
                            design_radial_get_major(rad));
        sprintf(text_minor, "mR%.*f",
                            design_dimension_get_precision(dim),
                            design_radial_get_minor(rad));
        cairo_text_extents(ctx, text_minor, &minor_extents);
      }
      else
        sprintf(text_major, "R%.*f",
                            design_dimension_get_precision(dim),
                            design_radial_get_major(rad));
      cairo_text_extents(ctx, text_major, &major_extents);
      break;
    case design_radial_type_diameter:
      if (design_radial_get_minor(rad))
      {
        sprintf(text_major, "M\u2300%.*f",
                            design_dimension_get_precision(dim),
                            design_radial_get_major(rad));
        sprintf(text_minor, "m\u2300%.*f",
                            design_dimension_get_precision(dim),
                            design_radial_get_minor(rad));
        cairo_text_extents(ctx, text_minor, &minor_extents);
      }
      else
        sprintf(text_major, "\u2300%.*f",
                            design_dimension_get_precision(dim),
                            design_radial_get_major(rad));
      cairo_text_extents(ctx, text_major, &major_extents);
      break;
    default: break;
  }
  text_width = fmax(major_extents.width, minor_extents.width);
  major_point = endpoint(leader_ext_end,
                         0,
                         (ext_side
                          * ((text_width / 2.0)
                            + design_dimension_get_text_size(dim))));
  untranslate_coords(major_point);
  if (design_radial_get_minor(rad))
  {
    minor_point = major_point;
    major_point = endpoint(major_point,
                           90,
                           design_dimension_get_text_size(dim) * 0.7);
    minor_point = endpoint(minor_point,
                           -90,
                           design_dimension_get_text_size(dim) * 0.7);
  }

    // scale vertices and lengths
  scale_coords(leader_start, design_element_get_units(e));
  scale_coords(leader_end, design_element_get_units(e));
  scale_coords(leader_ext_end, design_element_get_units(e));
  scale_coords(arrow_head, design_element_get_units(e));
  scale_coords(arrow_tail1, design_element_get_units(e));
  scale_coords(arrow_tail2, design_element_get_units(e));

  set_line_style(ctx, e->line_style);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a * 0.80);

    // render leader line
  cairo_move_to(ctx, leader_start->x, flip_y(sur, leader_start->y));
  cairo_line_to(ctx, leader_end->x, flip_y(sur, leader_end->y));
  cairo_stroke(ctx);
  cairo_move_to(ctx, leader_end->x, flip_y(sur, leader_end->y));
  cairo_line_to(ctx, leader_ext_end->x, flip_y(sur, leader_ext_end->y));
  cairo_stroke(ctx);

    // render arrow
  cairo_save(ctx);
  cairo_move_to(ctx, arrow_head->x, flip_y(sur, arrow_head->y));
  cairo_line_to(ctx, arrow_tail1->x, flip_y(sur, arrow_tail1->y));
  cairo_line_to(ctx, arrow_tail2->x, flip_y(sur, arrow_tail2->y));
  cairo_close_path(ctx);
  cairo_fill(ctx);
  cairo_stroke(ctx);
  cairo_restore(ctx);

  cairo_destroy(ctx);

    // render text
  el = design_element_create();
  design_element_set_type(el, design_element_type_text);
  design_text_set_type(el->text, design_text_type_drawing);
  design_text_set_location(el->text, major_point);
  design_text_set_anchor_point(el->text, design_anchor_location_type_center);
  design_text_set_size(el->text, design_dimension_get_text_size(dim));
  design_text_set_text(el->text, text_major);
  render_design_element_text(sur, el);
  design_element_destroy(el);
  if (design_radial_get_minor(rad))
  {
    el = design_element_create();
    design_element_set_type(el, design_element_type_text);
    design_text_set_type(el->text, design_text_type_drawing);
    design_text_set_location(el->text, minor_point);
    design_text_set_anchor_point(el->text, design_anchor_location_type_center);
    design_text_set_size(el->text, design_dimension_get_text_size(dim));
    design_text_set_text(el->text, text_minor);
    render_design_element_text(sur, el);
    design_element_destroy(el);
  }
}

static void render_design_element_elliptic(cairo_surface_t *sur,
                                           design_element_s *e)
{
  cairo_t *ctx;
  vertex_s *center;
  design_elliptic_s *ell;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (!clr) return;

  ell = design_element_get_elliptic(e);
  if (!ell) return;

  center = design_elliptic_get_center(ell);
  translate_coords(center);

  ctx = cairo_create(sur);

  set_line_style(ctx, e->line_style);
  cairo_set_line_width(ctx, design_element_get_line_weight(e));
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a);

  cairo_save(ctx);
  cairo_translate(ctx, 
                  scale(center->x, design_element_get_units(e)),
                  flip_y(sur, scale(center->y, design_element_get_units(e))));
  cairo_scale(ctx,
              scale(design_elliptic_get_width(ell),
                    design_element_get_units(e)),
              scale(design_elliptic_get_height(ell),
                    design_element_get_units(e)));
  cairo_arc(ctx, 0.0, 0.0,
            1.0,
            (360.0 - design_elliptic_get_end_angle(ell)) * (M_PI / 180.0),
            (360.0 - design_elliptic_get_start_angle(ell)) * (M_PI / 180.0));
  close_path(ctx, e);
  cairo_restore(ctx);
  cairo_stroke(ctx);

  fill(ctx, e);

  cairo_destroy(ctx);
}

static void render_design_element_line(cairo_surface_t *sur, design_element_s *e)
{
  cairo_t *ctx;
  vertex_s *start;
  vertex_s *end;
  design_line_s *lin;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (clr) return;

  lin = design_element_get_line(e);
  if (!lin) return;

  ctx = cairo_create(sur);

  set_line_style(ctx, e->line_style);
  cairo_set_line_width(ctx, design_element_get_line_weight(e));
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a);
  start = design_line_get_start(lin);
  translate_coords(start);
  end = design_line_get_end(lin);
  translate_coords(end);
  cairo_move_to(ctx,
                scale(start->x, design_element_get_units(e)),
                flip_y(sur, scale(start->y, design_element_get_units(e))));
  cairo_line_to(ctx,
                scale(end->x, design_element_get_units(e)),
                flip_y(sur, scale(end->y, design_element_get_units(e))));
  cairo_stroke(ctx);

  cairo_destroy(ctx);
}

static void render_design_element_point(cairo_surface_t *sur,
                                        design_element_s *e)
{
  cairo_t *ctx;
  vertex_s *location;
  design_point_s *pt;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (!clr) return;

  pt = design_element_get_point(e);
  if (!pt) return;

  location = design_point_get_location(pt);
  translate_coords(location);

  ctx = cairo_create(sur);

  set_line_style(ctx, e->line_style);
  cairo_set_line_width(ctx, design_element_get_line_weight(e));
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a);

  cairo_arc(ctx, 0.0, 0.0,
            design_element_get_line_weight(e),
            360.0 * (M_PI / 180.0),
            0.0);
  cairo_fill(ctx);

  cairo_destroy(ctx);
}

static void render_design_element_polyline(cairo_surface_t *sur,
                                           design_element_s *e)
{
  cairo_t *ctx;
  vertex_s *vertex;
  design_polyline_s *plin;
  vertices_s *vertices;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (clr) return;

  plin = design_element_get_polyline(e);
  if (!plin) return;

  vertices = design_polyline_get_vertices(plin);
  if (!vertices) return;

  ctx = cairo_create(sur);

  set_line_style(ctx, e->line_style);
  cairo_set_line_width(ctx, design_element_get_line_weight(e));
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a);

  vertex = (vertex_s *)list_head(vertices->vertices);
  if (!vertex) return;
  translate_coords(vertex);

  cairo_move_to(ctx,
                scale(vertex->x, design_element_get_units(e)),
                flip_y(sur, scale(vertex->y, design_element_get_units(e))));

  for (vertex = (vertex_s *)list_next(vertices->vertices);
       vertex;
       vertex = (vertex_s *)list_next(vertices->vertices))
  {
    translate_coords(vertex);
    cairo_line_to(ctx,
                  scale(vertex->x, design_element_get_units(e)),
                  flip_y(sur, scale(vertex->y, design_element_get_units(e))));
  }

  close_path(ctx, e);
  cairo_stroke(ctx);

  fill(ctx, e);

  cairo_destroy(ctx);
}

static void render_design_element_spline(cairo_surface_t *sur,
                                         design_element_s *e)
{
  cairo_t *ctx;
  vertex_s *v1;
  vertex_s *v2;
  vertex_s *v3;
  design_spline_s *spl;
  vertices_s *vertices;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (clr) return;

  spl = design_element_get_spline(e);
  if (!spl) return;

  vertices = design_spline_get_vertices(spl);
  if (!vertices) return;

  ctx = cairo_create(sur);

  set_line_style(ctx, e->line_style);
  cairo_set_line_width(ctx, design_element_get_line_weight(e));
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a);

  v1 = (vertex_s *)list_head(vertices->vertices);
  if (!v1) return;
  translate_coords(v1);

  cairo_move_to(ctx,
                scale(v1->x, design_element_get_units(e)),
                flip_y(sur, scale(v1->y, design_element_get_units(e))));

  for (v1 = (vertex_s *)list_next(vertices->vertices);
       v1;
       v1 = (vertex_s *)list_next(vertices->vertices))
  {
    v2 = (vertex_s *)list_next(vertices->vertices);
    v3 = (vertex_s *)list_next(vertices->vertices);
    if (!v2 || !v3) break;
    translate_coords(v1);
    translate_coords(v2);
    translate_coords(v3);
    cairo_curve_to(ctx,
                  scale(v1->x, design_element_get_units(e)),
                  flip_y(sur, scale(v1->y, design_element_get_units(e))),
                  scale(v2->x, design_element_get_units(e)),
                  flip_y(sur, scale(v2->y, design_element_get_units(e))),
                  scale(v3->x, design_element_get_units(e)),
                  flip_y(sur, scale(v3->y, design_element_get_units(e))));
  }

  close_path(ctx, e);
  cairo_stroke(ctx);

  fill(ctx, e);

  cairo_destroy(ctx);
}

static void render_design_element_text(cairo_surface_t *sur, design_element_s *e)
{
  cairo_t *ctx;
  cairo_text_extents_t text_ext;
  double x, y;
  double r;
  double rad;
  vertex_s *loc;
  design_text_s *txt;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (!clr) return;

  txt = design_element_get_text(e);
  if (!txt) return;

  ctx = cairo_create(sur);

  cairo_save(ctx);
  set_line_style(ctx, e->line_style);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a);
  cairo_select_font_face(ctx,
                         "monospace",
                         CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  switch (design_text_get_type(txt))
  {
    case design_text_type_drawing:
      cairo_set_font_size(ctx, scale(design_text_get_size(txt),
                                     design_element_get_units(e)));
      break;
    case design_text_type_annotation:
      //if (adj)
        cairo_set_font_size(ctx,
                            convert_to_points(design_text_get_size(txt),
                                              design_element_get_units(e)));
      //else
        //cairo_set_font_size(ctx, scale(e.text.text_size, e.units));
      //break;
  }
  cairo_text_extents(ctx, design_text_get_text(txt), &text_ext);

  set_text_extents(text_ext);

    // all calculation are from lower left of text extents
    //   offset by user location
  switch (design_text_get_anchor_point(txt))
  {
    case design_anchor_location_type_upper_left:
      x = 0.0;
      y = text_ext.height;
      break;
    case design_anchor_location_type_upper_right:
      y = text_ext.height;
      x = text_ext.width;
      break;
    case design_anchor_location_type_center:
      x = text_ext.width / 2.0;
      y = text_ext.height / 2.0;
      break;
    case design_anchor_location_type_lower_left:
      x = 0.0;
      y = 0.0;
      break;
    case design_anchor_location_type_lower_right:
      x = text_ext.width;
      y = 0.0;
      break;
  }

  r = sqrt((x * x) + (y * y));
  if (r)
  {
    rad = asin(y / r);
    rad += M_PI;
    rad += design_text_get_rotation(txt) * (M_PI / 180.0);
    x = r * cos(rad);
    y = r * sin(rad);
  }
  loc = design_text_get_location(txt);
  translate_coords(loc);
  x += scale(loc->x, design_element_get_units(e));
  y += scale(loc->y, design_element_get_units(e));
  y = flip_y(sur, y);

  cairo_move_to(ctx, x, y);
  cairo_rotate(ctx, (360.0 - design_text_get_rotation(txt)) * (M_PI / 180.0));
  cairo_show_text(ctx, design_text_get_text(txt));
  cairo_restore(ctx);

  cairo_destroy(ctx);
}

static void render_design_element_tolerance(cairo_surface_t *sur,
                                            design_element_s *e)
{
  cairo_t *ctx;
  vertex_s *box_upper_left;
  vertex_s *box_lower_right;
  vertex_s *plus_point;
  vertex_s *minus_point;
  char text_plus[40];
  char text_minus[40];
  cairo_text_extents_t plus_extents;
  cairo_text_extents_t minus_extents;
  design_element_s *el;
  design_tolerance_s *t;
  color_s *clr;

    // Sanity check parameters.
  assert(sur);
  assert(e);

  clr = design_element_get_color(e);
  if (!clr) return;

  t = design_element_get_tolerance(e);
  if (!t) return;

  memset(&plus_extents, 0, sizeof(cairo_text_extents_t));
  memset(&minus_extents, 0, sizeof(cairo_text_extents_t));
  memset(text_plus, 0, 40);
  memset(text_minus, 0, 40);

  ctx = cairo_create(sur);

    // prepare text
  cairo_set_font_size(ctx, design_tolerance_get_text_size(t));

  if (design_tolerance_get_plus(t) == design_tolerance_get_minus(t))
  {
    sprintf(text_plus, "\u00b1%.*f",
                       design_tolerance_get_precision(t),
                       design_tolerance_get_plus(t));
    cairo_text_extents(ctx, text_plus, &plus_extents);
  }
  else
  {
    sprintf(text_plus, "+%.*f",
                       design_tolerance_get_precision(t),
                       design_tolerance_get_plus(t));
    cairo_text_extents(ctx, text_plus, &plus_extents);
    sprintf(text_minus, "\u2212%.*f",
                       design_tolerance_get_precision(t),
                       design_tolerance_get_minus(t));
    cairo_text_extents(ctx, text_minus, &minus_extents);
  }
  
  plus_point = minus_point = design_tolerance_get_location(t);
  if (design_tolerance_get_plus(t) != design_tolerance_get_minus(t))
  {
    plus_point->y += design_tolerance_get_text_size(t) / 2.0;
    minus_point->y -= design_tolerance_get_text_size(t) / 2.0;
  }

  translate_coords(t->location);

  box_upper_left = vertex_copy(design_tolerance_get_location(t));
  box_lower_right = vertex_copy(design_tolerance_get_location(t));
  if (design_tolerance_get_plus(t) != design_tolerance_get_minus(t))
  {
    box_upper_left->x -= fmax(plus_extents.width, minus_extents.width) / 2.0;
    box_upper_left->y -= plus_extents.height * 0.65;
    box_lower_right->x += fmax(plus_extents.width, minus_extents.width) / 2.0;
    box_lower_right->y += minus_extents.height * 0.65;
  }
  else
  {
    box_upper_left->x -= fmax(plus_extents.width, minus_extents.width) / 2.0;
    box_upper_left->y -= fmax(plus_extents.height, minus_extents.height) / 2.85;
    box_lower_right->x += fmax(plus_extents.width, minus_extents.width) / 2.0;
    box_lower_right->y += fmax(plus_extents.height, minus_extents.height) / 2.85;
  }

  scale_coords(box_upper_left, design_element_get_units(e));
  scale_coords(box_lower_right, design_element_get_units(e));

  set_line_style(ctx, e->line_style);
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_set_source_rgba(ctx, clr->r, clr->g, clr->b, clr->a);
  cairo_set_line_width(ctx, design_element_get_line_weight(e));

    // render box
  cairo_move_to(ctx, box_upper_left->x, flip_y(sur, box_upper_left->y));
  cairo_line_to(ctx, box_lower_right->x, flip_y(sur, box_upper_left->y));
  cairo_line_to(ctx, box_lower_right->x, flip_y(sur, box_lower_right->y));
  cairo_line_to(ctx, box_upper_left->x, flip_y(sur, box_lower_right->y));
  cairo_close_path(ctx);
  cairo_stroke(ctx);
/*
  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

	cairo_rectangle(ctx,
                  box_upper_left.x,
                  flip_y(sur, box_upper_left.y),
                  box_lower_right.x - box_upper_left.x,
                  box_lower_right.y - box_upper_left.y);
*/

  cairo_destroy(ctx);

    // render text
  if (design_tolerance_get_plus(t) ||
      (design_tolerance_get_plus(t) == design_tolerance_get_minus(t)))
  {
    el = design_element_create();
    design_element_set_type(el, design_element_type_text);
    design_text_set_type(el->text, design_text_type_drawing);
    design_text_set_location(el->text, plus_point);
    design_text_set_anchor_point(el->text, design_anchor_location_type_center);
    design_text_set_size(el->text, design_tolerance_get_text_size(t));
    design_text_set_text(el->text, text_plus);
    render_design_element_text(sur, el);
    design_element_destroy(el);
  }
  if (design_tolerance_get_minus(t))
  {
    el = design_element_create();
    design_element_set_type(el, design_element_type_text);
    design_text_set_type(el->text, design_text_type_drawing);
    design_text_set_location(el->text, minus_point);
    design_text_set_anchor_point(el->text, design_anchor_location_type_center);
    design_text_set_size(el->text, design_tolerance_get_text_size(t));
    design_text_set_text(el->text, text_minus);
    render_design_element_text(sur, el);
    design_element_destroy(el);
  }
}

static double convert_to_points(double dim, units_t ut)
{
  double result;

  result = units_convert(dim, ut, units_type_point);

    // Return RETVAL
  return result;
}

  // This is always set in points
static cairo_rectangle_t paper_size(paper_s *p)
{
  cairo_rectangle_t rect;

    // Sanity check parameters.
  assert(p);

  rect.x = 0.0;
  rect.y = 0.0;

  rect.width = convert_to_points(p->width, p->units);
  rect.height = convert_to_points(p->height, p->units);

    // Return RETVAL
  return rect;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void get_surface_size(cairo_surface_t *surface, cairo_rectangle_t *rect)
{
  cairo_t *cr;
  double x1, x2, y1, y2;

    // Sanity check parameters.
  assert(surface);
  assert(rect);

  cr = cairo_create(surface);
  cairo_clip_extents(cr, &x1, &y1, &x2, &y2);
  cairo_destroy(cr);

  rect->x = x1;
  rect->y = y1;
  rect->width = x2 - x1;
  rect->height = y2 - y1;
}

static double _g_scale = 1.0;

static void set_design_scale(double scale)
{
  _g_scale = scale;
}

static double get_design_scale(void)
{
    // Return RETVAL
  return _g_scale;
}

static double scale(double coord, units_t units)
{
    // Return RETVAL
  return units_convert(coord, units, get_design_units()) * get_design_scale();
}

static vertex_s *adjust_vertex(vertex_s *v, double a, double d)
{
  vertex_s *nv;

    // Sanity check parameters.
  assert(v);

  nv = vertex_copy(v);

  nv->x -= (d * sin(a));
  nv->y += (d * cos(a));

    // Return RETVAL
  return nv;
}

static double flip_y(cairo_surface_t *sur, double y)
{
  cairo_rectangle_t sur_size;

    // Sanity check parameters.
  assert(sur);

  get_surface_size(sur, &sur_size);

  if (sur_size.height != INFINITY)
    y = sur_size.height - y - 1.0;

    // Return RETVAL
  return y;
}

static double _g_x_translation = 0.0;
static double _g_y_translation = 0.0;

static void set_x_translation(double x)
{
  _g_x_translation = x;
}

static double get_x_translation(void)
{
    // Return RETVAL
  return _g_x_translation;
}

static void set_y_translation(double y)
{
  _g_y_translation = y;
}

static double get_y_translation(void)
{
    // Return RETVAL
  return _g_y_translation;
}

static void translate_coords(vertex_s *v)
{
    // Sanity check parameters.
  assert(v);

  v->x -= _g_x_translation;
  v->y -= _g_y_translation;
}

static void untranslate_coords(vertex_s *v)
{
    // Sanity check parameters.
  assert(v);

  v->x += _g_x_translation;
  v->y += _g_y_translation;
}

static void scale_coords(vertex_s *v, units_t units)
{
    // Sanity check parameters.
  assert(v);

  v->x = scale(v->x, units);
  v->y = scale(v->y, units);
}

static cairo_text_extents_t _g_text_extents;

static void set_text_extents(cairo_text_extents_t tx)
{
  _g_text_extents = tx;
}

static cairo_text_extents_t get_text_extents(void)
{
    // Return RETVAL
  return _g_text_extents;
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

vertex_s *endpoint(vertex_s *pt, double a, double l)
{
  vertex_s *nv;

    // Sanity check parameters.
  assert(pt);

  nv = vertex_create();

  nv->x = pt->x + (l * cos(a));
  nv->y = pt->y + (l * sin(a));

    // Return RETVAL
  return nv;
}

static units_t _g_design_units = units_type_mm;

static void set_design_units(units_t units)
{
  _g_design_units = units;
}

static units_t get_design_units(void)
{
    // Return RETVAL
  return _g_design_units;
}

static design_line_styles_s *_g_design_line_styles = NULL;

static void set_design_line_styles(design_s *d)
{
  if (!d) return;
  if (d->line_styles) _g_design_line_styles = design_get_line_styles(d);
}

static design_line_styles_s *get_design_line_styles(void)
{
    // Return RETVAL
  return _g_design_line_styles;
}

static design_fill_styles_s *_g_design_fill_styles = NULL;

static void set_design_fill_styles(design_s *d)
{
  if (!d) return;
  if (d->fill_styles) _g_design_fill_styles = design_get_fill_styles(d);
}

static design_fill_styles_s *get_design_fill_styles(void)
{
    // Return RETVAL
  return _g_design_fill_styles;
}

static void set_line_style(cairo_t *ctx, char *style)
{
  design_line_styles_s *lss;
  design_line_style_s *ls;
  design_line_style_segments_s *segs;
  design_line_style_segment_s *seg;
  list_s *lst;
  int len;
  double *dvals;
  int i;

    // Sanity check parameters.
  assert(ctx);
  if (!style) { unset_line_style(ctx); return; }

  lss = get_design_line_styles();
  if (!lss) { unset_line_style(ctx); return; }

  ls = design_line_styles_get_line_style(lss, style);
  if (!ls) { unset_line_style(ctx); return; }

  if (!ls->line_style_segments) { unset_line_style(ctx); return; }

  segs = ls->line_style_segments;
  if (!segs->line_style_segments) { unset_line_style(ctx); return; }

  lst = segs->line_style_segments;

    // special line style "solid" turns off cairo_dash-ing
  if (!strcmp(ls->name, "solid")) { unset_line_style(ctx); return; }

  len = list_len(lst);

  dvals = (double *)malloc(sizeof(double) * len);

  for (seg = (design_line_style_segment_s *)list_head(lst), i = 0;
       seg;
       seg = (design_line_style_segment_s *)list_next(lst), i++)
  {
    dvals[i] = seg->length;
  }

  cairo_set_dash(ctx, dvals, len, 0.0);

  free(dvals);
}

static void unset_line_style(cairo_t *ctx)
{
    // Sanity check parameters.
  assert(ctx);
  cairo_set_dash(ctx, NULL, 0, 0.0);
}

static void close_path(cairo_t *ctx, design_element_s *e)
{
  if (e->fill_style
       && design_fill_styles_get_fill_style(get_design_fill_styles(),
                                            e->fill_style))
    cairo_close_path(ctx);
}

static void fill(cairo_t *ctx, design_element_s *e)
{
  design_fill_styles_s *fss;
  design_fill_style_s *fs;

  if (!e->fill_style) return;

  fss = get_design_fill_styles();
  if (!fss) return;

  fs = design_fill_styles_get_fill_style(fss, e->fill_style);
  if (!fs) return;


  switch (design_fill_style_get_type(fs))
  {
    case design_fill_style_type_line:
    case design_fill_style_type_hatch:
    case design_fill_style_type_stipple:
      fill_lhs(ctx, fs);
      break;
    case design_fill_style_type_source_only:
      fill_image(ctx, fs);
      break;
    default: return;
  }
}

static void fill_lhs(cairo_t *ctx, design_fill_style_s *fs)
{
  cairo_surface_t *surface;
  cairo_pattern_t *pattern;
  cairo_rectangle_t rect;
  cairo_t *cr;
  double x;
  double w, h;
  color_s *bgclr;
  color_s *patclr;
  double lw;
  char *ls = NULL;
  double angle1;
  double angle2;
  double spacing1;
  double spacing2;

    // Sanity check parameters.
  assert(ctx);
  assert(fs);

  angle1 = design_fill_style_get_angle1(fs);
  spacing1 = design_fill_style_get_spacing1(fs);
  angle2 = design_fill_style_get_angle2(fs);
  spacing2 = design_fill_style_get_spacing2(fs);
  bgclr = design_fill_style_get_background_color(fs);
  patclr = design_fill_style_get_pattern_color(fs);
  lw = design_fill_style_get_line_weight(fs);
  ls = design_fill_style_get_line_style(fs);

  angle1 *= 0.0174532925;
  angle2 *= 0.0174532925;

  get_surface_size(cairo_get_target(ctx), &rect);
  w = rect.width;
  h = rect.height;

  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
  cr = cairo_create(surface);

    // background color, default is none
  if (bgclr)
    cairo_set_source_rgba(cr, bgclr->r, bgclr->g, bgclr->b, bgclr->a);
  else
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0);
  cairo_rectangle(cr, 0.0, 0.0, w, h);
  cairo_fill(cr);

    // background image, if one exists
  if (fs->source)
    fill_image(ctx, fs);

  cairo_set_line_width(cr, lw);
  if (patclr)
    cairo_set_source_rgba(cr, patclr->r, patclr->g, patclr->b, patclr->a);
  else
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0);  // none, by default
  set_line_style(cr, ls);

  cairo_save(cr);
  cairo_rotate(cr, angle1);
  for (x = -(1.414 * w); x < (1.414 * w); x += spacing1)
  {
    cairo_move_to(cr, x, -(1.414 * h));
    cairo_line_to(cr, x, (1.414 * h));
  }
  cairo_stroke(cr);
  cairo_restore(cr);

  if ((fs->type == design_fill_style_type_hatch)
     || (fs->type == design_fill_style_type_stipple))
  {
    if (fs->type == design_fill_style_type_stipple)
      cairo_set_operator(cr, CAIRO_OPERATOR_IN);

    cairo_save(cr);
    cairo_rotate(cr, angle2);
    for (x = -(1.414 * w); x < (1.414 * w); x += spacing2)
    {
      cairo_move_to(cr, x, -(1.414 * h));
      cairo_line_to(cr, x, (1.414 * h));
    }
    cairo_stroke(cr);
    cairo_restore(cr);
  }

  cairo_destroy(cr);

  pattern = cairo_pattern_create_for_surface(surface);

  cairo_set_source(ctx, pattern);
  cairo_fill(ctx);

  pattern_destroy(pattern);
}

static void fill_image(cairo_t *ctx, design_fill_style_s *fs)
{
  cairo_surface_t *surface;
  cairo_pattern_t *pattern;

    // Sanity check parameters.
  assert(ctx);
  assert(fs);

  if (!fs->source) return;

  surface = cairo_image_surface_create_from_png(fs->source);

  pattern = cairo_pattern_create_for_surface(surface);
  cairo_pattern_set_extend(pattern, CAIRO_EXTEND_REFLECT);

  cairo_set_source(ctx, pattern);
  cairo_fill(ctx);

  pattern_destroy(pattern);
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

void pattern_destroy(cairo_pattern_t *pattern)
{
  cairo_surface_t *surface;

  cairo_pattern_get_surface(pattern, &surface);

  cairo_surface_destroy(surface);
  cairo_pattern_destroy(pattern);
}

