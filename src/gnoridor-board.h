#ifndef GNORIDOR_BOARD_H
#define GNORIDOR_BOARD_H

#include <gtk/gtk.h>

#include "gnoridor-player.h"
#include "gnoridor-cell.h"
#include "gnoridor-define.h"


extern int notify_player_signal;
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
	GtkWidget *curr_player_label;
};


/*
 * Method definitions.
 */

GnoridorBoard *gnoridor_board_new (void);
gboolean       gnoridor_board_request_move (GnoridorBoard *self, GnoridorPlayer *player, int direction);
void           gnoridor_board_set_window (GnoridorBoard *self, GtkWidget *window);
void           gnoridor_board_change_current_player(GnoridorBoard *self);
gboolean       gnoridor_board_can_place_wall (GnoridorBoard *self, GnoridorCell *cell, WallOrientation wall_or);
void           gnoridor_board_place_wall (GnoridorBoard *self, GnoridorCell *cell, WallOrientation wall_or);
void           gnoridor_board_reset (GnoridorBoard *self);
G_END_DECLS

#ifdef UNIT_TEST
GnoridorCell* run_check_dir(GnoridorBoard *b,
                            GnoridorCell *cell,
                            Direction     direction);
#endif



#endif
