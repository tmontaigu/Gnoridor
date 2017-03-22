#ifndef GNORIDOR_BOARD_H
#define GNORIDOR_BOARD_H

#include <gtk/gtk.h>

#include "gnoridor-player.h"
#include "gnoridor-cell.h"


int notify_player_signal;
GtkWidget *current_player_label;
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
	int number_of_player;
	GnoridorPlayer **player;
        int current_player_index;
	GnoridorPlayer *current_player;
	GnoridorCell **player_cell;
        
        gboolean placing_vertical_wall;
        gboolean placing_horizontal_wall;

	GtkWidget *window;
	GtkWidget *vwall_toggle;
	GtkWidget *hwall_toggle;
};


/*
 * Method definitions.
 */

GnoridorBoard *gnoridor_board_new (void);
gboolean       gnoridor_board_request_move (GnoridorBoard *self, GnoridorPlayer *player, int direction);
void           gnoridor_board_set_window (GnoridorBoard *self, GtkWidget *window);
void           gnoridor_board_change_current_player(GnoridorBoard *self);

G_END_DECLS

#endif
