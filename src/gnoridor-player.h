#ifndef GNORIDOR_PLAYER_H
#define GNORIDOR_PLAYER_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GNORIDOR_TYPE_PLAYER (gnoridor_player_get_type())

G_DECLARE_FINAL_TYPE (GnoridorPlayer, gnoridor_player, GNORIDOR, PLAYER, GtkPopover)

GnoridorPlayer *gnoridor_player_new (void);

G_END_DECLS

#endif /* GNORIDOR_PLAYER_H */

