AM_CFLAGS = -O3 -I .. -I $(top_srcdir)/include
AM_LDFLAGS =

lib_LTLIBRARIES = libblue.la libblue-xml.la

LDADD = libblue.la libblue-xml.la

libblue_la_SOURCES = border.c design.c design-anchor-location-type.c design-angular.c design-defaults.c design-dimension.c design-dimension-type.c design-element.c design-elements.c design-element-type.c design-elliptic.c design-fill-style.c design-fill-styles.c design-fill-style-type.c design-layer.c design-layers.c design-linear.c design-line.c design-line-style.c design-line-styles.c design-line-style-segment.c design-line-style-segments.c design-point.c design-polyline.c design-radial.c design-radial-type.c design-spline.c design-text.c design-text-type.c design-tolerance.c design-visibility-type.c drawing.c margins.c paper.c render-2d-cairo.c title-block.c units.c
libblue_la_LDFLAGS = -version-info 0:1:0
libblue_la_CFLAGS = ${AM_CFLAGS} ${CAIRO_CFLAGS} ${PANGO_CFLAGS} ${GRAY_CFLAGS}

libblue_xml_la_SOURCES = border-xml.c design-xml.c design-angular-xml.c design-defaults-xml.c design-dimension-xml.c design-elements-xml.c design-element-xml.c design-elliptic-xml.c design-fill-styles-xml.c design-fill-style-xml.c design-layers-xml.c design-layer-xml.c design-linear-xml.c design-line-style-segments-xml.c design-line-style-segment-xml.c design-line-styles-xml.c design-line-style-xml.c design-line-xml.c design-point-xml.c design-polyline-xml.c design-radial-xml.c design-spline-xml.c design-text-xml.c design-tolerance-xml.c drawing-xml.c margins-xml.c paper-xml.c title-block-xml.c
libblue_xml_la_LDFLAGS = -version-info 0:1:0
libblue_xml_la_CFLAGS = ${AM_CFLAGS} ${GRAY_CFLAGS} ${XML_CFLAGS}

.PHONY: timestamps
timestamps:
	@$(top_srcdir)/tools/auto-timestamp $(top_srcdir)

all: timestamps all-am
