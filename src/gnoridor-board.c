#include "gnoridor-board.h"
/* #include "gnoridor-cell.h" */
#include "gnoridor-player.h"
#include "callback.h"

G_DEFINE_TYPE (GnoridorBoard, gnoridor_board, GTK_TYPE_GRID);



GtkWidget *
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
							 GTK_WIDGET (self->cells[i][j]), i, j, 1,1);
		}
	}



	self->player1 = gnoridor_player_new_with_color (RED);
	gnoridor_cell_put_player (self->cells[4][0], self->player1);

	self->player2 = gnoridor_player_new_with_color (BLUE);
	gnoridor_cell_put_player (self->cells[4][8], self->player2);
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
