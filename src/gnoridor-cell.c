#include "gnoridor-cell.h"
#include "gnoridor-define.h"
#include "gnoridor-board.h"
#include "callback.h"

G_DEFINE_TYPE (GnoridorCell, gnoridor_cell, GTK_TYPE_DRAWING_AREA);

GnoridorCell *
gnoridor_cell_new (void)
{
	GnoridorCell *self = g_object_new (GNORIDOR_TYPE_CELL, NULL);
	return self;
}

static void
gnoridor_cell_class_init (GnoridorCellClass*class)
{

}

static void
gnoridor_cell_init (GnoridorCell *self)
{
	gtk_widget_add_events (GTK_WIDGET (self), GDK_BUTTON_PRESS_MASK);

	self->player_on_cell = NULL;
	self->vertical_wall = FALSE;
	self->horizontal_wall = FALSE;
}


void
gnoridor_cell_put_player (GnoridorCell *self, GnoridorPlayer *player)
{
	self->player_on_cell = player;
	gtk_popover_set_relative_to (GTK_POPOVER (player->actions), GTK_WIDGET (self));
}

void
gnoridor_cell_remove_player (GnoridorCell *self)
{
	self->player_on_cell = NULL;
}

gboolean
gnoridor_cell_is_not_empty (GnoridorCell *self){
	if (self->player_on_cell)
		 return TRUE;
	return FALSE;
}

GnoridorPlayer*
gnoridor_cell_get_player_on_cell (GnoridorCell *self) {
	if (gnoridor_cell_is_not_empty (self))
		return self->player_on_cell;
	return NULL;
}

void
gnoridor_cell_place_wall(GnoridorCell *self, WallOrientation wall_or)
{
	if (wall_or == Horizontal)
		self->horizontal_wall = TRUE;
	else if (wall_or == Vertical)
		self->vertical_wall = TRUE;
	gtk_widget_queue_draw ( GTK_WIDGET (self));
}

void
gnoridor_cell_place_temporary_wall(GnoridorCell *self, WallOrientation wall_or)
{
	if (wall_or == Horizontal)
		self->horizontal_wall = TRUE;
	else if (wall_or == Vertical)
		self->vertical_wall = TRUE;
}
void
gnoridor_cell_remove_temporary_wall(GnoridorCell *self, WallOrientation wall_or)
{
	if (wall_or == Horizontal)
		self->horizontal_wall = FALSE;
	else if (wall_or == Vertical)
		self->vertical_wall = FALSE;
}

void
gnoridor_cell_remove_walls(GnoridorCell *self)
{
  self->horizontal_wall = FALSE;
  self->vertical_wall = FALSE;
  gtk_widget_queue_draw (GTK_WIDGET (self));
}

void
gnoridor_cell_place_vertical_wall (GnoridorCell *self)
{
	self->vertical_wall = TRUE;
 	// Refresh the cell
	gtk_widget_queue_draw (GTK_WIDGET (self));
}

void
gnoridor_cell_place_horizontal_wall (GnoridorCell *self)
{
	self->horizontal_wall = TRUE;
	// Refresh the cell
	gtk_widget_queue_draw(GTK_WIDGET (self));
}

gboolean
gnoridor_cell_vertical_wall (GnoridorCell *self)
{
	return self->vertical_wall;
}

gboolean
gnoridor_cell_horizontal_wall (GnoridorCell *self)
{
	return self->horizontal_wall;
}
//TODO should probably be done with flags
int
gnoridor_cell_get_border_type (GnoridorCell *self)
{
	if (self->row == 0)
	{
		// if (self->col == 0)
		// 	return Up_left_corner;
		// if (self->col == 8)
		// 	return Up_right_corner;
		return Up_border;
	}

	if (self->row == NUMBER_OF_ROWS - 1)
	{
		// if (self->col == 0)
		// 	return Bottom_left_corner;
		// if (self->col == 8)
		// 	return Bottom_right_corner;
		return Bottom_border;
	}
	if (self->col == 0)
		return Left_border;
	if (self->col == NUMBER_OF_COLS - 1)
		return Right_border;

	return Not_border;
}

gboolean
gnoridor_cell_is_border (GnoridorCell *self)
{
	if ( (self->row > 0 && self->row < NUMBER_OF_ROWS - 1) &&
	   (self->col > 0 && self->col < NUMBER_OF_COLS - 1))
		return FALSE;
	return TRUE;
}

gboolean
gnoridor_cell_click(GnoridorCell *self, GdkEvent *event, gpointer data) {
	GnoridorBoard *board = data;
	// Vertical wall
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (board->vwall_toggle)))
	{
		if (board->current_player->number_of_walls <= 0)
		{
			show_dialog_window("You don't have any wall left !", board->window);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (board->hwall_toggle), FALSE);
			return FALSE;
		}

		if (gnoridor_cell_get_border_type (self) == Bottom_border ||
			gnoridor_cell_get_border_type (self) == Right_border  ||
			self->vertical_wall)
		{
			show_dialog_window("You cannot place a wall here !", board->window);
			return FALSE;
		}
		if (gnoridor_board_can_place_wall (board, self, Vertical))
		{
			gnoridor_board_place_wall (board, self, Vertical);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (board->vwall_toggle), FALSE);

			board->current_player->number_of_walls--;
			gnoridor_board_change_current_player (board);
			return FALSE; // Player's turn is over
		}
		else
		{
			show_dialog_window ("You cannot place wall in a way that splits the board\n", board->window);
			return FALSE;
		}
	}
	// Horizontal wall
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (board->hwall_toggle)))
	{
		if (board->current_player->number_of_walls <= 0)
		{
			show_dialog_window("You don't have any wall left !", board->window);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (board->hwall_toggle), FALSE);
			return FALSE;
		}

		if (gnoridor_cell_get_border_type (self) == Bottom_border ||
			gnoridor_cell_get_border_type (self) == Right_border  ||
			self->horizontal_wall)
		{
			show_dialog_window("You cannot place a wall here !", board->window);
			return FALSE;
		}

		if (gnoridor_board_can_place_wall (board, self	, Horizontal))
		{
			gnoridor_board_place_wall (board, self, Horizontal);
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (board->hwall_toggle), FALSE);

			board->current_player->number_of_walls--;
			gnoridor_board_change_current_player (board);
			return FALSE;
		}
		else
		{
			show_dialog_window ("You cannot place wall in a way that splits the board\n", board->window);
			return FALSE;
		}
	}

	if (self->player_on_cell && board->current_player == self->player_on_cell)
		gtk_popover_popup (GTK_POPOVER (self->player_on_cell->actions));
	return FALSE;
}

static void draw_horizontal_wall(cairo_t *cr, guint width, guint height, int border) {
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

static void draw_vertical_wall(cairo_t *cr, guint width, guint height, int border) {
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


static void draw_cell(cairo_t *cr, guint width, guint height, guint size)
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

static void draw_player(cairo_t *cr, guint width, guint height, guint size) {
	double radius = size / 8;
	double x_center = width / 2;
	double y_center = height / 2;

	cairo_arc(cr, x_center, y_center, radius, 0, 2 * 3.1415);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
}

gboolean
gnoridor_cell_draw (GtkWidget *widget, cairo_t *cr, gpointer data)
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
