#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <cairo-svg.h>
#include <cairo-pdf.h>
#include <cairo-ps.h>
#include <time.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "render-2d-cairo.h"
#include "drawing-xml.h"

int main(int argc, char** argv)
{
  drawing_s *d;
  paper_s *p;
  border_s *b;
  title_block_s *tb;
  design_s *de;
  margins_s *m;
  design_layer_s *ly;
  design_element_s *el;
  vertex v;
  cairo_surface_t *r_sur;
  cairo_surface_t *o_sur;
  cairo_t *ctx;
  cairo_rectangle_t rect;
  design_anchor_location_t i;
  char t[80];
  double rot;
  xmlDocPtr doc;

  m = margins_create();
  margins_set_units(m, units_type_in);
  margins_set_top(m, 0.25);
  margins_set_bottom(m, 0.25);
  margins_set_left(m, 0.25);
  margins_set_right(m, 0.25);

  p = paper_create();
  // AutoMagic in paper.c : p = paper_set_units(p, units_type_in);
  paper_set_orientation(p, paper_orientation_type_portrait);
  //paper_set_orientation(p, paper_orientation_type_landscape);
  paper_set_size(p, paper_size_type_letter);
  paper_set_margins(p, m);

  tb = title_block_create();
  title_block_set_title(tb, "Test Window Design");
  title_block_set_part(tb, "PART 1A-0O-42.9 WIDGET");
  title_block_set_revision(tb, "A1");
  title_block_set_reference(tb, "M-TW-1");
  title_block_set_provider(tb, "Patrick Head LLC");
  title_block_set_consumer(tb, "Patrick Head");
  title_block_set_page(tb, 1);
  title_block_set_of(tb, 1);
  title_block_set_time(tb, time(NULL));

  b = border_create();
  border_set_units(b, units_type_in);
  border_set_margins(b, m);

  margins_destroy(m);

  de = design_create();
  ly = design_layer_create();
  //design_layer_set_id(ly, 0);
  design_layer_set_name(ly, "DEFAULT");
  design_layer_set_visibility(ly, design_visibility_type_visible);

#if 0 // line
  el = design_element_create();
  design_element_set_type(el, design_element_type_line);
  //design_element_set_line_weight(el, 1.5);
  vertex_set(v, 0, 0, 0);
  design_element_set_start(el, v);
  vertex_set(v, 10, 10, 0);
  //vertex_set(v, 1, 1, 0);
  design_element_set_end(el, v);
  design_layer_add_element(ly, el);
#endif // line

#if 0 // linear dimension
  el = design_element_create();
  design_element_set_type(el, design_element_type_dimension);
  //design_element_set_line_weight(el, 1.0);
  design_element_set_dimension_type(el, design_element_dimension_type_linear);
/*
  design_element_set_gap(el, 0.1);
  design_element_set_extension_above(el, 0.025);
  design_element_set_extension_below(el, 0.075);
  design_element_set_text_size(el, 0.1);
  design_element_set_precision(el, 10);
*/
  //design_element_set_dimension(el, 2);
  vertex_set(v, 0, 0, 0);
  design_element_set_start(el, v);
  vertex_set(v, 10, 10, 0);
  //vertex_set(v, 1, 1, 0);
  design_element_set_end(el, v);
  design_layer_add_element(ly, el);
#endif // linear dimension

#if 0 // angular dimension
  el = design_element_create();
  design_element_set_type(el, design_element_type_dimension);
  //design_element_set_line_weight(el, 1.0);
  design_element_set_dimension_type(el, design_element_dimension_type_angular);
  design_element_set_gap(el, 1.0);
  design_element_set_extension(el, 7.0);
  //design_element_set_text_size(el, 0.1);
  design_element_set_precision(el, 1);
  vertex_set(v, 0, 0, 0);
  design_element_set_alpha(el, v);
  vertex_set(v, 10, 10, 0);
  design_element_set_beta(el, v);
  vertex_set(v, 10, 0, 0);
  design_element_set_gamma(el, v);
  design_layer_add_element(ly, el);
#endif // angular dimension

#if 0 // radial dimension
  el = design_element_create();
  design_element_set_type(el, design_element_type_dimension);
  //design_element_set_line_weight(el, 1.0);
  design_element_set_dimension_type(el, design_element_dimension_type_radial);
  design_element_set_text_size(el, 0.5);
  design_element_set_precision(el, 1);
  vertex_set(v, 5, 5, 0);
  design_element_set_center(el, v);
  design_element_set_major(el, 5.0);
  //design_element_set_minor(el, 3.0);
  design_element_set_radial_type(el, design_radial_type_diameter);
  design_element_set_angle(el, 315.0);
  design_element_set_leader(el, 7.0);
  design_layer_add_element(ly, el);
#endif // angular dimension

#if 1 // radial dimension
  el = design_element_create();
  design_element_set_type(el, design_element_type_tolerance);
  //design_element_set_line_weight(el, 1.0);
  design_element_set_text_size(el, 0.5);
  design_element_set_precision(el, 3);
  vertex_set(v, 5, 5, 0);
  design_element_set_location(el, v);
  design_element_set_plus(el, 0.003);
  design_element_set_minus(el, 0.003);
  design_layer_add_element(ly, el);
#endif // angular dimension

/*
// ******* Opens to right
  el = design_element_create();
  design_element_set_type(el, design_element_type_dimension);
  design_element_set_line_weight(el, 1.0);
  design_element_set_dimension_type(el, design_element_dimension_type_angular);
  design_element_set_gap(el, 1.0);
  design_element_set_extension(el, 5.0);
  design_element_set_text_size(el, 0.1);
  design_element_set_precision(el, 1);
  //design_element_set_angle(el, 30.0);
  vertex_set(v, 5, 5, 0);
  design_element_set_alpha(el, v);
  vertex_set(v, 9, 9, 0);
  design_element_set_beta(el, v);
  vertex_set(v, 9, 1, 0);
  design_element_set_gamma(el, v);
  design_layer_add_element(ly, el);
// ******* Opens up
  el = design_element_create();
  design_element_set_type(el, design_element_type_dimension);
  design_element_set_line_weight(el, 1.0);
  design_element_set_dimension_type(el, design_element_dimension_type_angular);
  design_element_set_gap(el, 1.0);
  design_element_set_extension(el, 5.0);
  design_element_set_text_size(el, 0.1);
  design_element_set_precision(el, 1);
  //design_element_set_angle(el, 30.0);
  vertex_set(v, 5, 5, 0);
  design_element_set_alpha(el, v);
  vertex_set(v, 1, 9, 0);
  design_element_set_beta(el, v);
  vertex_set(v, 9, 9, 0);
  design_element_set_gamma(el, v);
  design_layer_add_element(ly, el);
*/
/*
// ******* Opens to left
  el = design_element_create();
  design_element_set_type(el, design_element_type_dimension);
  design_element_set_line_weight(el, 1.0);
  design_element_set_dimension_type(el, design_element_dimension_type_angular);
  design_element_set_gap(el, 1.0);
  design_element_set_extension(el, 2.0);
  design_element_set_text_size(el, 0.5);
  //design_element_set_precision(el, 2);
  design_element_set_precision(el, 0);
  //design_element_set_angle(el, 30.0);
  vertex_set(v, 5, 5, 0);
  design_element_set_alpha(el, v);
  vertex_set(v, 1, 1, 0);
  design_element_set_beta(el, v);
  vertex_set(v, 1, 9, 0);
  design_element_set_gamma(el, v);
  design_layer_add_element(ly, el);
// ******* Opens down
  el = design_element_create();
  design_element_set_type(el, design_element_type_dimension);
  design_element_set_line_weight(el, 1.0);
  design_element_set_dimension_type(el, design_element_dimension_type_angular);
  design_element_set_gap(el, 1.0);
  design_element_set_extension(el, 5.0);
  design_element_set_text_size(el, 0.1);
  design_element_set_precision(el, 1);
  //design_element_set_angle(el, 30.0);
  vertex_set(v, 5, 5, 0);
  design_element_set_alpha(el, v);
  vertex_set(v, 9, 1, 0);
  design_element_set_beta(el, v);
  vertex_set(v, 1, 1, 0);
  design_element_set_gamma(el, v);
  design_layer_add_element(ly, el);
*/

/*
  el = design_element_create();
  design_element_set_type(el, design_element_type_line);
  vertex_set(v, 30, 50, 0);
  design_element_set_start(el, v);
  vertex_set(v, 30, 30, 0);
  design_element_set_end(el, v);
  design_layer_add_element(ly, el);

  el = design_element_create();
  design_element_set_type(el, design_element_type_elliptic);
  //design_element_set_line_weight(el, 0.5);
  vertex_set(v, 50, 50, 0);
  design_element_set_center(el, v);
  design_element_set_width(el, 20);
  design_element_set_height(el, 20);
  //design_element_set_start_angle(el, 270);
  design_element_set_start_angle(el, 0);
  //design_element_set_end_angle(el, 360);
  design_element_set_end_angle(el, 180);
  design_layer_add_element(ly, el);
*/

/*
  for (i = design_anchor_location_type_upper_left;
       i <= design_anchor_location_type_lower_right;
       i++)
  {
    for (rot = 0.0; rot <= 360.0; rot += 90.0)
    {
      el = design_element_create();
      design_element_set_type(el, design_element_type_text);
      design_element_set_text_type(el, design_text_type_drawing);
      //design_element_set_text_type(el, design_text_type_annotation);
      vertex_set(v, 50, 30 + (i * 10), 0);
      design_element_set_location(el, v);
      design_element_set_text_size(el, 3);
      //design_element_set_text_size(el, 1.0/6.0);
      sprintf(t, "Text %d", i);
      design_element_set_text(el, t);
      design_element_set_rotation(el, rot);
      design_element_set_anchor_point(el, i);
      design_layer_add_element(ly, el);
    }
  }
*/

  design_add_layer(de, ly);

  d = drawing_create();
  drawing_set_paper(d, p);
  drawing_set_title_block(d, tb);
  drawing_set_border(d, b);
  drawing_set_design(d, de);

  r_sur = render_2d_cairo(d);

    // Test for XML stuff
  doc = drawing_to_xml(d);
  xmlSaveFormatFileEnc("stuff/test.xml", doc, "UTF-8", 1);
  //xmlSaveFile("stuff/test.xml", doc);
  xmlFreeDoc(doc);

  drawing_destroy(d);

  get_surface_size(r_sur, &rect);
  o_sur = cairo_svg_surface_create("stuff/test.svg", rect.width, rect.height);
  //o_sur = cairo_pdf_surface_create("stuff/test.pdf", rect.width, rect.height);
  //o_sur = cairo_ps_surface_create("stuff/test.ps", rect.width, rect.height);
  ctx = cairo_create(o_sur);
  cairo_set_source_surface(ctx, r_sur, 0.0, 0.0);
  cairo_paint(ctx);
  cairo_show_page(ctx);
  cairo_destroy(ctx);
  cairo_surface_destroy(o_sur);

  cairo_surface_destroy(r_sur);

  return 0;
}

