#include <gtk/gtk.h>

#include "callback.h"
#include "gnoridor-cell.h"

// TODO Find a way to draw the GnoridorCell depending on the size of the
// GtkGrid that contains it.
// TODO Add drawing of player
// TODO Add drawing of walls (maybe not so good idea)
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

gboolean
click_cell_callback (GnoridorCell *cell, gpointer data) {

	if (cell->player_on_cell)
	{
		printf("There is a player here\n");
		gtk_popover_popup (GTK_POPOVER (cell->player_on_cell));

	}
	else
		printf("There is no player here\n");

	return FALSE;
}

gboolean
closed_callback (GtkPopover *pop, gpointer data) {
	printf("closed signal\n");
}
