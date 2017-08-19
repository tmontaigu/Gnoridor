#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>

#include "gnoridor-cell.h"
#include "gnoridor-player.h"
#include "gnoridor-board.h"
#include "gnoridor-define.h"

GnoridorBoard *game_board;

typedef struct PlayerButtonCb_t
{
	GnoridorPlayer *player;
	GnoridorBoard *board;
}PlayerButtonCb;


/*
 * function that draws the rectangle which represent the border of the board
 */
gboolean draw_board_limit(GtkWidget *widget, cairo_t *cr, gpointer data);


gboolean player_changed_callback(GnoridorBoard *board, gpointer data);

/*
 * callbacks connected to their respective buttons
 * They set a boolean in the game board
 * so the click_cell callback can check if the player wants to place a wall
 */
void prepare_vertical_wall_callback(GtkWidget *button, gpointer data);
void prepare_horizontal_wall_callback(GtkWidget *button, gpointer data);
void show_dialog_window(char *text);

/* player mouvement buttons callback */
void up_button_callback(GtkWidget *button, gpointer data);
void down_button_callback(GtkWidget *button, gpointer data);
void left_button_callback(GtkWidget *button, gpointer data);
void right_button_callback(GtkWidget *button, gpointer data);

#endif
