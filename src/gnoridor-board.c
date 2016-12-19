#include "gnoridor-board.h"
#include "gnoridor-player.h"
#include "callback.h"

#include <stdlib.h>

G_DEFINE_TYPE (GnoridorBoard, gnoridor_board, GTK_TYPE_GRID);



GnoridorBoard *
gnoridor_board_new (void)
{
	return g_object_new (GNORIDOR_TYPE_BOARD, NULL);
}

static void
gnoridor_board_class_init (GnoridorBoardClass *class)
{
	printf("gnoridor_board_class_init\n");
}

// Constructeur, c'est appeller lors du g_object_new
static void
gnoridor_board_init (GnoridorBoard *self)
{
	GtkBuilder *builder = gtk_builder_new_from_resource ("/org/gtk/gnoridor/resources/ui/action-popover.ui");
	GtkBuilder *builder2 = gtk_builder_new_from_resource ("/org/gtk/gnoridor/resources/ui/action-popover.ui");

	gtk_grid_set_column_homogeneous (GTK_GRID (self), TRUE);
	gtk_grid_set_row_homogeneous    (GTK_GRID (self), TRUE);

	// Create cells and position them on the grid
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			self->cells[i][j] = gnoridor_cell_new ();
			self->cells[i][j]->row = i;
			self->cells[i][j]->col = j;

			gtk_grid_attach (GTK_GRID (self),
							 GTK_WIDGET (self->cells[i][j]), j, i, 1,1);
		}
	}


	self->number_of_player = 2;
	self->player = malloc (sizeof * self->player * self->number_of_player);
	self->player_cell = malloc (sizeof * self->player_cell * self->number_of_player);


	GnoridorPlayer *p = gnoridor_player_new_with_color (BLUE);
	gnoridor_cell_put_player (self->cells[0][4], p);
	self->player_cell[0] = self->cells[0][4];
	self->player[0] = p;

	p = gnoridor_player_new_with_color (RED);
	gnoridor_cell_put_player (self->cells[8][4], p);
	self->player_cell[1] = self->cells[8][4];
	self->player[1] = p;


}


static void
gnoridor_board_dispose (GObject *gobject)
{
  G_OBJECT_CLASS (gnoridor_board_parent_class)->dispose (gobject);
}

static void
gnoridor_cell_finalize (GObject *gobject)
{
  G_OBJECT_CLASS (gnoridor_board_parent_class)->finalize (gobject);
}

static GnoridorPlayer*
gnoridor_board_get_player(GnoridorBoard *self, int color_id)
{
	for (int i = 0; i < self->number_of_player; i++) {
		if (self->player[i]->id == color_id)
			return self->player[i];
	}
}

static GnoridorCell*
gnoridor_board_get_player_cell(GnoridorBoard *self, int color_id)
{
	for (int i = 0; i < self->number_of_player; i++) {
		if (self->player[i]->id == color_id)
			return self->player_cell[i];
	}
}

static void
gnoridor_board_set_player_cell(GnoridorBoard *self, int color_id, GnoridorCell *new_cell)
{
	for (int i = 0; i < self->number_of_player; i++) {
		if (self->player[i]->id == color_id)
			self->player_cell[i] = new_cell;
	}
}


static GnoridorCell *
gnoridor_board_check_move_validity (GnoridorBoard *self, GnoridorCell *old_cell,
																		int direction)
{
	GnoridorCell *new_cell = NULL;

	switch (direction) {
	case Up:
		if (old_cell->row-1 < 0)
			return NULL;
		new_cell = self->cells[old_cell->row-1][old_cell->col];
		break;
	case Down:
		if ( old_cell->row+1 > 9)
			return NULL;
		new_cell = self->cells[old_cell->row+1][old_cell->col];
		break;
	case Left:
		if (old_cell->col-1 < 0)
			return NULL;
		new_cell = self->cells[old_cell->row][old_cell->col-1];
		break;
	case Right:
		if (old_cell->col+1 >= 9)
			return NULL;
		new_cell = self->cells[old_cell->row][old_cell->col+1];
		break;
	}

	if (gnoridor_cell_is_not_empty (new_cell))
		new_cell = NULL;



	return new_cell;
}


gboolean
gnoridor_board_request_move(GnoridorBoard *self, GnoridorPlayer *player, int direction)
{

	GnoridorCell *old_cell = gnoridor_board_get_player_cell (self, player->id);
	GnoridorCell *new_cell = gnoridor_board_check_move_validity (self,
																															 old_cell,
																															 direction);


	if (new_cell == NULL) {
		printf("invalid move\n");
		return FALSE;
	}


	gnoridor_cell_remove_player (old_cell);
	gnoridor_cell_put_player (new_cell, player);
	gnoridor_board_set_player_cell(self, player->id, new_cell);
	return TRUE;
}
