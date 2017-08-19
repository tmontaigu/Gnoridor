#include <gtk/gtk.h>

#include "callback.h"
#include "gnoridor-cell.h"
#include "gnoridor-player.h"
#include "gnoridor-board.h"
#include "gnoridor-define.h"




// TODO Maybe drawing squares instead of rectangle should be better


// If the cell is the borders we can't place a wall since,
// walls expands to the cell below or to the right
// obvilously don't put a wall if there's already one

// TODO using border prevents from putting wall starting on top row
// or most-left col
// TODO The best thing would be to make button untoggable when all walls are placed


gboolean
draw_board_limit (GtkWidget *widget, cairo_t *cr, gpointer data) {
	GtkAllocation *board_allocation = g_new (GtkAllocation, 1);
	gtk_widget_get_allocation (widget, board_allocation);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 0);

	int offset = 5;
	cairo_rectangle(cr,
			offset,
			offset,
			board_allocation->width - 2*offset,
			board_allocation->height - 2*offset);

	cairo_set_line_width(cr, 4);
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
	cairo_stroke(cr);
	return TRUE;
}


gboolean
player_changed_callback (GnoridorBoard *board, gpointer data)
{
	printf("PLAYER CHANGED\n");
	return FALSE;
}

void show_dialog_window(char *text)
{
	GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW (game_board->window),
												flags,
												GTK_MESSAGE_ERROR,
												GTK_BUTTONS_CLOSE,
												"%s", text);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

}

void prepare_horizontal_wall_callback (GtkWidget *button, gpointer data)
{
	GnoridorBoard *board = data;
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (board->vwall_toggle), FALSE);
	board->placing_horizontal_wall = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));
}

void prepare_vertical_wall_callback (GtkWidget *button, gpointer data)
{
	GnoridorBoard *board = data;
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (board->hwall_toggle), FALSE);
	board->placing_vertical_wall = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));
}

//------------------------------------------------------------------------------
// BUTTONS CALLBACKS
//------------------------------------------------------------------------------


void
up_button_callback (GtkWidget *button, gpointer data) {
	PlayerButtonCb *d = data;
	int succesful = gnoridor_board_request_move(d->board, d->player, Up);
	if (succesful) {
		gnoridor_board_change_current_player(d->board);
		gtk_popover_popdown (GTK_POPOVER (d->player->actions));
	}
}

void
down_button_callback (GtkWidget *button, gpointer data) {
	PlayerButtonCb *d = data;
	int succesful = gnoridor_board_request_move(d->board, d->player, Down);
	if (succesful) {
		gnoridor_board_change_current_player(d->board);
		gtk_popover_popdown (GTK_POPOVER (d->player->actions));
	}
}

void
left_button_callback (GtkWidget *button, gpointer data) {
	PlayerButtonCb *d = data;
	int succesful = gnoridor_board_request_move(d->board, d->player, Left);
	if (succesful) {
		gnoridor_board_change_current_player(d->board);
		gtk_popover_popdown (GTK_POPOVER (d->player->actions));
	}
}

void
right_button_callback (GtkWidget *button, gpointer data) {
	PlayerButtonCb *d = data;
	int succesful = gnoridor_board_request_move(d->board, d->player, Right);
	if (succesful) {
		gnoridor_board_change_current_player(d->board);
		gtk_popover_popdown (GTK_POPOVER (d->player->actions));
	}
}

