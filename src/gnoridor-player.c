#include "gnoridor-player.h"

struct _GnoridorPlayer
{
	GtkPopover parent_instance;
};

G_DEFINE_TYPE (GnoridorPlayer, gnoridor_player, GTK_TYPE_POPOVER)

GnoridorPlayer *
gnoridor_player_new (void)
{
	return g_object_new (GNORIDOR_TYPE_PLAYER, NULL);
}

static void
gnoridor_player_finalize (GObject *object)
{
	GnoridorPlayer *self = (GnoridorPlayer *)object;

	G_OBJECT_CLASS (gnoridor_player_parent_class)->finalize (object);
}

static void
gnoridor_player_class_init (GnoridorPlayerClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	object_class->finalize = gnoridor_player_finalize;
}

static void
gnoridor_player_init (GnoridorPlayer *self)
{
}
