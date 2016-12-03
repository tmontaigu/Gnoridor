#ifndef GNORIDOR_CELL_H
#define GNORIDOR_CELL_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GNORIDOR_TYPE_CELL (gnoridor_cell_get_type())

G_DECLARE_FINAL_TYPE (GnoridorCell, gnoridor_cell, GNORIDOR, CELL, GtkDrawingArea)

/*
 * Members declaration.
 */

struct _GnoridorCell
{
	GtkDrawingArea parent_instance;

	/* Other members, including private data. */
	GtkWidget *player_on_cell;
};


/*
 * Method definitions.
 */
GnoridorCell *gnoridor_cell_new (void);
void          gnoridor_cell_put_player (GnoridorCell *self, GtkWidget *player);

G_END_DECLS

#endif /* GNORIDOR_CELL_H */

