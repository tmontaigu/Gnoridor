#ifndef GNORIDOR_PLAYER_H
#define GNORIDOR_PLAYER_H

#include  <gtk/gtk.h>




typedef struct _playerColor {
	double r;
	double g;
	double b;
}playerColor;


#define NUM_COLORS
typedef enum {
	RED, BLUE
}Colors;


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
	int id;
        char name[5];
};


GnoridorPlayer *gnoridor_player_new (void);
GnoridorPlayer *gnoridor_player_new_with_color (int color);
void gnoridor_player_color (GnoridorPlayer *self, cairo_t *cr);
void gnoridor_player_set_color (GnoridorPlayer *self, int color );
void gnoridor_player_color_int_to_char (GnoridorPlayer *self);

G_END_DECLS



#endif /* GNORIDOR_PLAYER_H */

