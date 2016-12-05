#ifndef GNORIDOR_BOARD_H
#define GNORIDOR_BOARD_H

#include <gtk/gtk.h>

#include "gnoridor-player.h"
#include "gnoridor-cell.h"

G_BEGIN_DECLS


/*
 * Type declaration.
 */

#define GNORIDOR_TYPE_BOARD (gnoridor_board_get_type ())
G_DECLARE_FINAL_TYPE (GnoridorBoard, gnoridor_board, GNORIDOR, BOARD, GtkGrid);


/*
 * Members declaration.
 */

struct _GnoridorBoard
{
	GtkGrid parent_instance;

	/* Other members, including private data. */
	GnoridorCell *cells[9][9];
	GnoridorPlayer *player1;
	GnoridorPlayer *player2;
};


/*
 * Method definitions.
 */


GtkWidget *gnoridor_board_new (void);
void       gnoridor_board_set_player_cell (int player, int col, int row);

G_END_DECLS

#endif
