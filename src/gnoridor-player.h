#ifndef GNORIDOR_PLAYER_H
#define GNORIDOR_PLAYER_H

#include  <gtk/gtk.h>

typedef struct _playerColor {
	double r;
	double g;
	double b;
}playerColor;

#define RED  0
#define BLUE 1


G_BEGIN_DECLS

#define GNORIDOR_TYPE_PLAYER (gnoridor_player_get_type())

G_DECLARE_FINAL_TYPE (GnoridorPlayer, gnoridor_player, GNORIDOR, PLAYER, GtkWidget)

struct _GnoridorPlayer
{
	GtkWidget parent_instance;

	/* Other members, including private data. */
	GtkBuilder *builder;
	GtkWidget *actions;
	playerColor color;
};


GnoridorPlayer *gnoridor_player_new (void);
GnoridorPlayer *gnoridor_player_new_with_color (int color);
void gnoridor_player_color (GnoridorPlayer *self, cairo_t *cr);
void gnoridor_player_set_color (GnoridorPlayer *self, int color );

G_END_DECLS

/* player mouvement buttons callback */
void up_button_callback (GtkWidget *button, gpointer data);
void down_button_callback (GtkWidget *button, gpointer data);
void left_button_callback (GtkWidget *button, gpointer data);
void right_button_callback (GtkWidget *button, gpointer data);

#endif /* GNORIDOR_PLAYER_H */

