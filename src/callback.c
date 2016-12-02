#include <gtk/gtk.h>

#include "callback.h"

struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;

/* this is how we will draw the cells of the grid */
void do_drawing(cairo_t *cr, guint width, guint height)
{
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 4.5);

	cairo_rectangle(cr, 0, 0, 50, 50);
	cairo_set_line_width(cr, 4);
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
	cairo_stroke(cr);
}

gboolean
draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
	guint width, height;
	do_drawing(cr, width, height);
	return FALSE;
}
