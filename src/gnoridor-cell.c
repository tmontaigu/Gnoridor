#include "gnoridor-cell.h"
#include "callback.h"

G_DEFINE_TYPE (GnoridorCell, gnoridor_cell, GTK_TYPE_DRAWING_AREA);



GnoridorCell *
gnoridor_cell_new (void)
{
	return g_object_new (GNORIDOR_TYPE_CELL, NULL);
}

static void
gnoridor_cell_class_init (GnoridorCellClass*class)
{
	printf("gnoridor_cell_class_init\n");
}

// Constructeur, c'est appeller lors du g_object_new
static void
gnoridor_cell_init (GnoridorCell *self)
{
	//printf("gnoridor_cell_init\n");
	gtk_widget_add_events (GTK_WIDGET (self), GDK_BUTTON_PRESS_MASK);
	self->player_on_cell = NULL;
	g_signal_connect (G_OBJECT   (self), "draw",
					  G_CALLBACK (draw_callback), NULL);
	g_signal_connect (G_OBJECT   (self), "button_press_event",
					  G_CALLBACK (click_cell_callback), NULL);
}


void
gnoridor_cell_put_player (GnoridorCell *self, GtkWidget *player)
{
	self->player_on_cell = player;

}

static void
gnoridor_cell_dispose (GObject *gobject)
{
  G_OBJECT_CLASS (gnoridor_cell_parent_class)->dispose (gobject);
}

static void
gnoridor_cell_finalize (GObject *gobject)
{
  G_OBJECT_CLASS (gnoridor_cell_parent_class)->finalize (gobject);
}
