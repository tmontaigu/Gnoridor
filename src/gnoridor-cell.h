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

        gboolean vertical_wall;
        gboolean horizontal_wall;
        
	int row;
	int col;
};


/*
 * Method definitions.
 */
GnoridorCell   *gnoridor_cell_new (void);
void           gnoridor_cell_put_player (GnoridorCell *self, GnoridorPlayer *player);
void           gnoridor_cell_remove_player (GnoridorCell *self);
void           gnoridor_cell_place_vertical_wall (GnoridorCell *self);
void           gnoridor_cell_place_horizontal_wall (GnoridorCell *self);
gboolean       gnoridor_cell_is_not_empty (GnoridorCell *self);
gboolean       gnoridor_cell_vertical_wall (GnoridorCell *self);
gboolean       gnoridor_cell_horizontal_wall (GnoridorCell *self);
GnoridorPlayer *gnoridor_cell_get_player_on_cell (GnoridorCell *self);
gboolean       gnoridor_cell_is_border (GnoridorCell *self);
int            gnoridor_cell_get_border_type (GnoridorCell *self);

G_END_DECLS

#endif /* GNORIDOR_CELL_H */

