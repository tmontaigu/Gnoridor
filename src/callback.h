#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>

#include "gnoridor-cell.h"
#include "gnoridor-player.h"
#include "gnoridor-board.h"


typedef enum {
	Up, Down, Left, Right
}Direction;


GnoridorBoard *game_board;
/*
 * Callback where we do all the drawing stuff.
 * The cell draws itself, draws the player icon,
 * draws the walls
 *
 */
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
/*
 * Callback when the user clicks on a cell
 * Behaviour :
 * 	if a player is on the cell:
 *     Show the popover with the possible directions to move the player.
 * 	else
 *     Do nothing
 */
gboolean click_cell_callback (GnoridorCell *cell, gpointer data);
gboolean closed_callback (GtkPopover *pop, gpointer data);

gboolean draw_board_limit (GtkWidget *widget, cairo_t *cr, gpointer data);

/* player mouvement buttons callback */
void up_button_callback (GtkWidget *button, gpointer data);
void down_button_callback (GtkWidget *button, gpointer data);
void left_button_callback (GtkWidget *button, gpointer data);
void right_button_callback (GtkWidget *button, gpointer data);

#endif
