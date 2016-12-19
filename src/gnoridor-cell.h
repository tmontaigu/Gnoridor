#ifndef GNORIDOR_CELL_H
#define GNORIDOR_CELL_H

#include <gtk/gtk.h>

#include "gnoridor-player.h"


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
	GnoridorPlayer *player_on_cell;

	int row;
	int col;
};


/*
 * Method definitions.
 */
GnoridorCell   *gnoridor_cell_new (void);
void           gnoridor_cell_put_player (GnoridorCell *self, GnoridorPlayer *player);
void           gnoridor_cell_remove_player (GnoridorCell *self);
gboolean       gnoridor_cell_is_not_empty (GnoridorCell *self);
GnoridorPlayer *gnoridor_cell_get_player_on_cell (GnoridorCell *self);

G_END_DECLS

#endif /* GNORIDOR_CELL_H */

