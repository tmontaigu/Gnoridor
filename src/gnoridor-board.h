#ifndef GNORIDOR_BOARD_H
#define GNORIDOR_BOARD_H

#include <gtk/gtk.h>


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
	GtkWidget *board;
	GtkWidget *player1;
	GtkWidget *player2;
};


/*
 * Method definitions.
 */


GtkWidget *gnoridor_board_new (void);

G_END_DECLS

#endif
