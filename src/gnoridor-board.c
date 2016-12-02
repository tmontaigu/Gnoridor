#include "gnoridor-board.h"
#include "gnoridor-cell.h"

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
	printf("gnoridor_board_init\n");
	gtk_grid_set_column_homogeneous (GTK_GRID (self), TRUE);
	gtk_grid_set_row_homogeneous    (GTK_GRID (self), TRUE);

    GtkWidget *buttons[81];
	GnoridorCell *cells[81];

	for (int i = 0; i < 81; i++)
	{
		//buttons[i] = gtk_button_new_with_label ("Cell");
		cells[i] = gnoridor_cell_new ();
	}


	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			gtk_grid_attach (GTK_GRID (self),
							 GTK_WIDGET (cells[i + (j * 9)]), i, j, 1,1);
		}
	}
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
