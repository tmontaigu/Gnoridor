/* main.c
 *
 * Copyright (C) 2016 Thomas
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>

#include "gnoridor-board.h"
#include "callback.h"

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
	GtkWidget *window;
	GtkWidget *header_bar;
	GtkWidget *board;


	// Init Window
	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Gnoridor");
	gtk_window_set_default_size (GTK_WINDOW (window), 640, 400);


	// The header bar
	header_bar = gtk_header_bar_new ();
	gtk_header_bar_set_title (GTK_HEADER_BAR (header_bar), "Gnoridor");
	gtk_header_bar_set_subtitle (GTK_HEADER_BAR (header_bar), "Merde");
	gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header_bar), TRUE);

	// Replace the title bar with that new shiny header bar
	gtk_window_set_titlebar (GTK_WINDOW (window), header_bar);


	 GtkWidget *board_limit = gtk_drawing_area_new ();
	/* gtk_widget_set_size_request (draw, 640, 400); */
	 g_signal_connect (G_OBJECT (board_limit), "draw",
	 				  G_CALLBACK (draw_board_limit), NULL);

	board = gnoridor_board_new ();


	GtkWidget *overlay = gtk_overlay_new ();
	gtk_overlay_add_overlay (GTK_OVERLAY (overlay), board_limit);
	gtk_overlay_add_overlay (GTK_OVERLAY (overlay), GTK_WIDGET (board));


	gtk_container_add (GTK_CONTAINER (window), overlay);
	gtk_widget_show_all (window);
}

int main(int   argc,
         char *argv[])
{
	g_autoptr(GtkApplication) app = NULL;
	int status;

	app = gtk_application_new ("org.gnome.Gnoridor", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);



	return status;
}