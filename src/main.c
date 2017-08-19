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

void
new_game_callback (GtkWidget *new_game_bt, gpointer data)
{
	GnoridorBoard *board = data;
	gnoridor_board_reset (board);
}


static void
activate (GtkApplication *app,
		  gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *header_bar;
	GnoridorBoard *board;

	// Init Window
	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Gnoridor");
	gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);

	// Thear header bar
	header_bar = gtk_header_bar_new ();
	gtk_header_bar_set_title (GTK_HEADER_BAR (header_bar), "Gnoridor");
	gtk_header_bar_set_subtitle (GTK_HEADER_BAR (header_bar), "Merde");
	gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header_bar), TRUE);

	// Replace the title bar with that new shiny header bar
	gtk_window_set_titlebar (GTK_WINDOW (window), header_bar);

	// Draw board limit
	GtkWidget *board_limit = gtk_drawing_area_new ();
	g_signal_connect (G_OBJECT (board_limit), "draw",
					  G_CALLBACK (draw_board_limit), NULL);

	board = gnoridor_board_new ();
	gnoridor_board_set_window (board, window);

	GtkWidget *new_game_bt = gtk_button_new_with_label ("New Game");
	g_signal_connect (new_game_bt, "clicked", G_CALLBACK (new_game_callback), board);

	gtk_container_add (GTK_CONTAINER (header_bar), new_game_bt);

	GtkWidget *overlay = gtk_overlay_new ();
	gtk_overlay_add_overlay (GTK_OVERLAY (overlay), board_limit);
	gtk_overlay_add_overlay (GTK_OVERLAY (overlay), GTK_WIDGET (board));

	GtkWidget *game_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

	// TODO: change ugly global variable to a GnoridorBoard member
	char label_text[25];
	sprintf(label_text, "Current player:\nBlue");
	current_player_label = gtk_label_new (label_text);

	GtkWidget *place_hwall_button, *place_vwall_button;
	place_hwall_button = gtk_toggle_button_new_with_label ("Place Horizontal Wall");
	place_vwall_button = gtk_toggle_button_new_with_label ("Place Vertical Wall");

	gtk_toggle_button_set_mode (GTK_TOGGLE_BUTTON (place_hwall_button), FALSE);
	gtk_toggle_button_set_mode (GTK_TOGGLE_BUTTON (place_vwall_button), FALSE);

	/*
	g_signal_connect (place_hwall_button, "toggled",
					  G_CALLBACK (prepare_horizontal_wall_callback),
					  board);

	g_signal_connect (place_vwall_button, "toggled",
					  G_CALLBACK (prepare_vertical_wall_callback),
					  board);
	*/

	board->vwall_toggle = place_vwall_button;
	board->hwall_toggle = place_hwall_button;

	GtkWidget *box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);
	gtk_box_set_homogeneous (GTK_BOX (box), FALSE);
	gtk_container_add (GTK_CONTAINER (box), current_player_label);
	gtk_container_add (GTK_CONTAINER (box), place_vwall_button);
	gtk_container_add (GTK_CONTAINER (box), place_hwall_button);

	gtk_box_pack_start (GTK_BOX (game_box), overlay, TRUE, TRUE, 5);
	gtk_box_pack_start (GTK_BOX (game_box), box, FALSE, FALSE, 5);

	gtk_container_add (GTK_CONTAINER (window), game_box);
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
