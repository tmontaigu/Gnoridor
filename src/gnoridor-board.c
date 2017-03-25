#include "gnoridor-board.h"
#include "gnoridor-player.h"
#include "callback.h"

#include <stdlib.h>
#include <gtk/gtk.h>

G_DEFINE_TYPE (GnoridorBoard, gnoridor_board, GTK_TYPE_GRID);

GnoridorBoard *
gnoridor_board_new (void)
{
    return g_object_new (GNORIDOR_TYPE_BOARD, NULL);
}

static void
gnoridor_board_class_init (GnoridorBoardClass *class)
{
	notify_player_signal = g_signal_newv("notify_player",
                            G_TYPE_FROM_CLASS (class),
                            G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                            NULL /* closure */,
                            NULL /* accumulator */,
                            NULL /* accumulator data */,
                            NULL /* C marshaller */,
                            G_TYPE_NONE /* return_type */,
                            0     /* n_params */,
                            NULL  /* param_types */);
	printf("gnoridor_board_class_init\n");
}

// Constructeur, c'est appeller lors du g_object_new
static void
gnoridor_board_init (GnoridorBoard *self)
{
        g_signal_connect (G_OBJECT (self), "notify_player",
                          G_CALLBACK (player_changed_callback), NULL);

	gtk_grid_set_column_homogeneous (GTK_GRID (self), TRUE);
	gtk_grid_set_row_homogeneous    (GTK_GRID (self), TRUE);

	// Create cells and position them on the grid
	for (int i = 0; i < NUMBER_OF_ROWS; i++)
	{
		for (int j = 0; j < NUMBER_OF_COLS; j++)
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



        // Create 2 players
	GnoridorPlayer *p = gnoridor_player_new_with_color (BLUE);
	gnoridor_cell_put_player (self->cells[0][4], p);
	self->player_cell[0] = self->cells[0][4];
	self->player[0] = p;
	p->number_of_walls = NUMBER_OF_WALLS / self->number_of_player;

	p = gnoridor_player_new_with_color (RED);
	gnoridor_cell_put_player (self->cells[8][4], p);
	self->player_cell[1] = self->cells[8][4];
	self->player[1] = p;
	p->number_of_walls = NUMBER_OF_WALLS / self->number_of_player;

        // Player 0 is the first one to start
	self->current_player = self->player[0];
        self->current_player_index = 0;

	self->window = NULL;
	self->placing_vertical_wall = FALSE;
}


static GnoridorCell*
gnoridor_board_get_player_cell(GnoridorBoard *self, int color_id)
{
	for (int i = 0; i < self->number_of_player; i++) {
		if (self->player[i]->id == color_id)
			return self->player_cell[i];
	}
	return NULL;
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
		if (gnoridor_cell_horizontal_wall(new_cell))
			return NULL;
		break;
	case Down:
		if ( old_cell->row+1 > 9)
                    return NULL;
		new_cell = self->cells[old_cell->row+1][old_cell->col];
		if (gnoridor_cell_horizontal_wall(old_cell))
			return NULL;
		break;
	case Left:
		if (old_cell->col-1 < 0)
                    return NULL;
		new_cell = self->cells[old_cell->row][old_cell->col-1];
		if (gnoridor_cell_vertical_wall(new_cell))
			return NULL;
		break;
	case Right:
		if (old_cell->col+1 >= 9)
                    return NULL;
		new_cell = self->cells[old_cell->row][old_cell->col+1];
		if (gnoridor_cell_vertical_wall(old_cell))
			return NULL;
		break;
	}

	if (gnoridor_cell_is_not_empty (new_cell))
		new_cell = NULL;
	return new_cell;
}

static gboolean
gnoridor_board_check_win (GnoridorBoard *self, GnoridorPlayer *player)
{
	GnoridorCell *cell = gnoridor_board_get_player_cell (self, player->id);
	int border_type = gnoridor_cell_get_border_type (cell);

	if (player->id == RED &&  border_type == Up_border)
	{
		printf("GG player %d\n", player->id);
		return TRUE;
	}
	if (player->id == BLUE && border_type == Bottom_border)
	{
		printf("GG player %d\n", player->id);
		return TRUE;
	}
	return FALSE;
}

gboolean
gnoridor_board_request_move(GnoridorBoard *self, GnoridorPlayer *player, int direction)
{

	GnoridorCell *old_cell = gnoridor_board_get_player_cell (self, player->id);
	GnoridorCell *new_cell = gnoridor_board_check_move_validity (self,
                                                                     old_cell,
                                                                     direction);


	if (new_cell == NULL) {
		show_dialog_window("You cannot move in this direction");
		return FALSE;
	}

        if (self->current_player != player)
        {
		printf("Not players turn\n");
		// To make sure the AI won't be able to move multiple times
		gtk_popover_popdown( GTK_POPOVER (player->actions));
		return FALSE;
        }

	gnoridor_cell_remove_player (old_cell);
	gnoridor_cell_put_player (new_cell, player);
	gnoridor_board_set_player_cell(self, player->id, new_cell);
	gboolean player_wins = gnoridor_board_check_win (self, player);
	if (player_wins) // show popup window
	{
		char text[20];
		sprintf(text, "%s player wins", player->name);
		show_dialog_window(text);

	}
	return TRUE;
}

void gnoridor_board_change_current_player(GnoridorBoard* self) {
	self->current_player_index = (self->current_player_index + 1) % self->number_of_player;
	self->current_player = self->player[self->current_player_index];
	//g_signal_emit_by_name(self, "player_changed");
	char label_text[45];
	sprintf(label_text, "Current player:\n%s\nRemaining walls: %d", self->current_player->name,
																	self->current_player->number_of_walls);


	if (self->current_player->number_of_walls > 0)
	{
		gtk_widget_set_sensitive(GTK_WIDGET (self->hwall_toggle), TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET (self->vwall_toggle), TRUE);
	}
	else
	{
		gtk_widget_set_sensitive(GTK_WIDGET (self->hwall_toggle), FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET (self->vwall_toggle), FALSE);
	}

	gtk_label_set_text (GTK_LABEL (current_player_label), label_text);
}


void
gnoridor_board_set_window (GnoridorBoard *self, GtkWidget *window)
{
	self->window = window;
}

