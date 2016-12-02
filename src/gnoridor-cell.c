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
	printf("gnoridor_cell_init\n");
	//gtk_widget_set_size_request (GTK_DRAWING_AREA (self), 50, 50);
	g_signal_connect (G_OBJECT   (self), "draw",
					  G_CALLBACK (draw_callback), NULL);
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
