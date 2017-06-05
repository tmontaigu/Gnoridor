#include <gtk/gtk.h>

#include "callback.h"
#include "gnoridor-cell.h"
#include "gnoridor-player.h"
#include "gnoridor-board.h"
#include "gnoridor-define.h"


void draw_horizontal_wall(cairo_t *cr, guint width, guint height, int border) {
	double start_x = 0;
	double start_y = height;
	double end_x   = width;
	double end_y   = height;

	if (border == Left_border || border == Up_left_corner)
	  start_x += 5;
	if (border == Right_border || border == Up_right_corner)
	  end_x -= 5;
	if (border == Bottom_border || border == Bottom_left_corner ||
	    border == Bottom_right_corner)
	  return;
	cairo_set_source_rgb(cr, 1, 0, 0);
	cairo_set_line_width(cr, 7);

	cairo_move_to (cr, start_x, start_y);
	cairo_line_to (cr, end_x, end_y);

	cairo_stroke(cr);
}

void draw_vertical_wall(cairo_t *cr, guint width, guint height, int border) {
	double start_x = width;
	double start_y =  0;
	double end_x   = width;
	double end_y   = height;

	if (border == Up_border || border == Up_left_corner)
		start_y += 5;
	if (border == Bottom_border || border == Bottom_left_corner)
		end_y -= 5;
	if (border == Right_border || border == Bottom_right_corner ||
            border == Up_right_corner)
		return;


	cairo_set_source_rgb(cr, 1, 0, 0);
	cairo_set_line_width(cr, 7);

	cairo_move_to (cr, start_x, start_y);
	cairo_line_to (cr, end_x, end_y);

	cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
	cairo_stroke(cr);
}


void draw_cell(cairo_t *cr, guint width, guint height, guint size)
{
	double x_center = width / 2;
	double y_center = height / 2;

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 4.5);

	cairo_rectangle(cr, x_center - size / 4,
                        y_center - size / 4,
                        size / 2 ,
                        size / 2);

	cairo_set_line_width(cr, 4);
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
	cairo_stroke(cr);
}

void draw_player(cairo_t *cr, guint width, guint height, guint size) {
	double radius = size / 8;
	double x_center = width / 2;
	double y_center = height / 2;

	cairo_arc(cr, x_center, y_center, radius, 0, 2 * 3.1415);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
}

// TODO Maybe drawing squares instead of rectangle should be better
gboolean
draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
	GtkAllocation *cell_allocation = g_new (GtkAllocation, 1);
	gtk_widget_get_allocation (widget, cell_allocation);

	double width = cell_allocation->width;
	double height = cell_allocation->height;
	double size = width < height ? 1.25*width : 1.25*height;


	draw_cell(cr, width, height, size);
	if (gnoridor_cell_is_not_empty (GNORIDOR_CELL (widget)))
	{
		gnoridor_player_color (gnoridor_cell_get_player_on_cell( GNORIDOR_CELL(widget)),
									 cr);
		draw_player(cr, width, height, size);
	}

	if (gnoridor_cell_horizontal_wall(GNORIDOR_CELL (widget)))
	{
		draw_horizontal_wall (cr, cell_allocation->width, cell_allocation->height,
				      gnoridor_cell_get_border_type (GNORIDOR_CELL (widget)));
	}
	if (gnoridor_cell_vertical_wall(GNORIDOR_CELL (widget)))
	{
		draw_vertical_wall (cr, cell_allocation->width, cell_allocation->height,
				    gnoridor_cell_get_border_type (GNORIDOR_CELL (widget)));
	}
	return FALSE;
}

// If the cell is the borders we can't place a wall since,
// walls expands to the cell below or to the right
// obvilously don't put a wall if there's already one

// TODO using border prevents from putting wall starting on top row
// or most-left col
// TODO The best thing would be to make button untoggable when all walls are placed
gboolean
click_cell_callback (GnoridorCell *cell, gpointer data) {
	// Vertical wall
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (game_board->vwall_toggle)))
	{
		if (game_board->current_player->number_of_walls <= 0)
		{
			show_dialog_window("You don't have any wall left !");
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (game_board->hwall_toggle), FALSE);
			return FALSE;
		}

		if (gnoridor_cell_get_border_type (cell) == Bottom_border ||
		    gnoridor_cell_get_border_type (cell) == Right_border  ||
		    cell->vertical_wall)
		{
			show_dialog_window("You cannot place a wall here !");
			return FALSE;
		}
		if (gnoridor_board_can_place_wall (game_board, cell, Vertical))
		{
      gnoridor_board_place_wall (game_board, cell, Vertical);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (game_board->vwall_toggle), FALSE);

			game_board->current_player->number_of_walls--;
			gnoridor_board_change_current_player (game_board);
			return FALSE; // Player's turn is over
		}
    else
    {
      show_dialog_window ("You cannot place wall in a way that splits the board\n");
      return FALSE;
    }
	}
	// Horizontal wall
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (game_board->hwall_toggle)))
	{
		if (game_board->current_player->number_of_walls <= 0)
		{
			show_dialog_window("You don't have any wall left !");
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (game_board->hwall_toggle), FALSE);
			return FALSE;
		}

		if (gnoridor_cell_get_border_type (cell) == Bottom_border ||
			gnoridor_cell_get_border_type (cell) == Right_border  ||
			cell->horizontal_wall)
		{
			show_dialog_window("You cannot place a wall here !");
			return FALSE;
		}
		gnoridor_cell_place_horizontal_wall (cell);

		// Also place a wall on the cell on the right
		GnoridorCell *right = game_board->cells[cell->row][cell->col+1];
		gnoridor_cell_place_horizontal_wall (right);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (game_board->hwall_toggle), FALSE);

		game_board->current_player->number_of_walls--;
		printf("g: %d\n", game_board->current_player->number_of_walls);
		gnoridor_board_change_current_player (game_board);
		return FALSE; // Player's turn is over
	}

	if (cell->player_on_cell && game_board->current_player == cell->player_on_cell)
            gtk_popover_popup (GTK_POPOVER (cell->player_on_cell->actions));
	return FALSE;
}


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
	GnoridorPlayer *player = data;
	int succesful = gnoridor_board_request_move(game_board, player, Up);
        if (succesful) {
            gnoridor_board_change_current_player(game_board);
            gtk_popover_popdown (GTK_POPOVER (player->actions));
        }
}

void
down_button_callback (GtkWidget *button, gpointer data) {
	GnoridorPlayer *player = data;
	int succesful = gnoridor_board_request_move(game_board, player, Down);
        if (succesful) {
            gnoridor_board_change_current_player(game_board);
            gtk_popover_popdown (GTK_POPOVER (player->actions));
        }
}

void
left_button_callback (GtkWidget *button, gpointer data) {
	GnoridorPlayer *player = data;
	int succesful = gnoridor_board_request_move(game_board, player, Left);
        if (succesful) {
            gnoridor_board_change_current_player(game_board);
            gtk_popover_popdown (GTK_POPOVER (player->actions));
        }
}

void
right_button_callback (GtkWidget *button, gpointer data) {
	GnoridorPlayer *player = data;
	int succesful = gnoridor_board_request_move(game_board, player, Right);
        if (succesful) {
            gnoridor_board_change_current_player(game_board);
            gtk_popover_popdown (GTK_POPOVER (player->actions));
        }
}

