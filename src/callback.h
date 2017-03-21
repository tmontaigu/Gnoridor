#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>

#include "gnoridor-cell.h"
#include "gnoridor-player.h"
#include "gnoridor-board.h"
#include "gnoridor-define.h"

GnoridorBoard *game_board;
/*
 * Callback where we do all the drawing stuff.
 * The cell draws itself, draws the player icon,
 * draws the walls
 *
 */
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);


/*
 * function that draws the rectangle which represent the border of the board
 */
gboolean draw_board_limit (GtkWidget *widget, cairo_t *cr, gpointer data);


/*
 * Callback when the user clicks on a cell
 * Behaviour :
 *  if the action is to place a wall, this callback handles the different calls
 *  to place them.
 *
 *  if a player is on the cell:
 *    Show the popover with the possible directions to move the player.
 */
gboolean click_cell_callback (GnoridorCell *cell, gpointer data);


gboolean player_changed_callback (GnoridorBoard *board, gpointer data);


/*
 * callbacks connected to their respective buttons
 * They set a boolean in the game_board
 * so the click_cell callback can check if the player wants to place a wall
 */
void prepare_vertical_wall_callback (GtkWidget *button, gpointer data);
void prepare_horizontal_wall_callback (GtkWidget *button, gpointer data);

void show_dialog_window(char *text);

/* player mouvement buttons callback */
void up_button_callback (GtkWidget *button, gpointer data);
void down_button_callback (GtkWidget *button, gpointer data);
void left_button_callback (GtkWidget *button, gpointer data);
void right_button_callback (GtkWidget *button, gpointer data);

#endif
