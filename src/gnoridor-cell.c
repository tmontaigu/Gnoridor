#include "gnoridor-cell.h"

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
