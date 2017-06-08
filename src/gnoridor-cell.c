#include "gnoridor-cell.h"
#include "callback.h"
#include "gnoridor-define.h"

G_DEFINE_TYPE (GnoridorCell, gnoridor_cell, GTK_TYPE_DRAWING_AREA);



GnoridorCell *
gnoridor_cell_new (void)
{
	return g_object_new (GNORIDOR_TYPE_CELL, NULL);
}

static void
gnoridor_cell_class_init (GnoridorCellClass*class)
{

}

static void
gnoridor_cell_init (GnoridorCell *self)
{
	gtk_widget_add_events (GTK_WIDGET (self), GDK_BUTTON_PRESS_MASK);

	g_signal_connect (G_OBJECT   (self), "draw",
					  G_CALLBACK (draw_callback), NULL);
	g_signal_connect (G_OBJECT   (self), "button_press_event",
					  G_CALLBACK (click_cell_callback), NULL);

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

GnoridorPlayer  *
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
