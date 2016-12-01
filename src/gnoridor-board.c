#include "gnoridor-board.h"

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
	//self->board = gtk_grid_new ();
	self->player1 = gtk_button_new_with_label ("KOUKOU");
	gtk_container_add (GTK_CONTAINER (self), self->player1);
	//gtk_widget_show_all (self);
}


static void
gnoridor_board_dispose (GObject *gobject)
{
  G_OBJECT_CLASS (gnoridor_board_parent_class)->dispose (gobject);
}

static void
viewer_file_finalize (GObject *gobject)
{
  G_OBJECT_CLASS (gnoridor_board_parent_class)->finalize (gobject);
}
