#include <gtk/gtk.h>

#include "callback.h"
#include "gnoridor-cell.h"


void draw_cell(cairo_t *cr, guint width, guint height)
{
	double x_center = width / 2;
	double y_center = height / 2;

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 4.5);

	cairo_rectangle(cr, x_center - width / 4,
					y_center - height / 4,
					width / 2 ,
					height / 2);

	cairo_set_line_width(cr, 4);
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
	cairo_stroke(cr);
}

// TODO Add drawing of player
// TODO Add drawing of walls (maybe not so good idea)
gboolean
draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
	GtkAllocation *cell_allocation = g_new (GtkAllocation, 1);
	gtk_widget_get_allocation (widget, cell_allocation);

	printf("x: %d, y: %d\n", cell_allocation->width, cell_allocation->height);
	guint width, height;
	draw_cell(cr, cell_allocation->width, cell_allocation->height);
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
