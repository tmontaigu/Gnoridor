#ifndef GNORIDOR_CELL_H
#define GNORIDOR_CELL_H

#include <gtk/gtk.h>

#include "gnoridor-player.h"
#include "gnoridor-define.h"

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

/*
 * Creates a new GnoridorCell instance
 * Connects the draw and click callbacks
 * Initialize the cell as empty (no player, no walls)
 */
GnoridorCell   *gnoridor_cell_new (void);


/*
 * Puts the player on the cell
 */
void           gnoridor_cell_put_player (GnoridorCell *self, GnoridorPlayer *player);


/*
 * Removes the player from the cell
 */
void           gnoridor_cell_remove_player (GnoridorCell *self);

void           gnoridor_cell_place_wall (GnoridorCell *self, WallOrientation wall_or);
void           gnoridor_cell_place_temporary_wall (GnoridorCell *self, WallOrientation wall_or);
void           gnoridor_cell_remove_temporary_wall(GnoridorCell *self, WallOrientation wall_or);

/*
 * Places a vertical wall on the right side of the cell itself and the one
 * below it
 */
void           gnoridor_cell_place_vertical_wall (GnoridorCell *self);


/*
 * Places horizontal wall on the cell bottom side of the cell itself and the one
 * on its right
 */
void           gnoridor_cell_place_horizontal_wall (GnoridorCell *self);


/*
 * Tells if there is a player on the cell
 *   returns TRUE if there is one, FALSE otherwise
 */
gboolean       gnoridor_cell_is_not_empty (GnoridorCell *self);


/*
 * returns TRUE if there is a vertical wall assigned to the cell,
 * returns FALSE otherwise
 */
gboolean       gnoridor_cell_vertical_wall (GnoridorCell *self);


/*
 * returns TRUE if there is a horizontal wall assigned to the cell,
 * returns FALSE otherwise
 */
gboolean       gnoridor_cell_horizontal_wall (GnoridorCell *self);


/*
 * Returns the player on the cell
 * if there is no player, returns NULL
 */
GnoridorPlayer *gnoridor_cell_get_player_on_cell (GnoridorCell *self);


/*
 * Returns TRUE of the cell is border cell, FALSE otherwise
 * A border cell is a cell that is at least at one of these locations:
 *  - Top row
 *  - Bottom row
 *  - Leftmost column
 *  - Rightmost colum
 */
gboolean       gnoridor_cell_is_border (GnoridorCell *self);

/*
 * Returns the type of border that the cell belongs to
 * Types can be found in the Border_type enum in the
 * gnoridor-define.h header
 */
int            gnoridor_cell_get_border_type (GnoridorCell *self);

G_END_DECLS

#endif /* GNORIDOR_CELL_H */

