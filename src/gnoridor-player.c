#include "gnoridor-player.h"
#include "gnoridor-cell.h"

G_DEFINE_TYPE (GnoridorPlayer, gnoridor_player, GTK_TYPE_WIDGET)

GnoridorPlayer *
gnoridor_player_new (void)
{
	GnoridorPlayer *self = g_object_new (GNORIDOR_TYPE_PLAYER, NULL);
	self->builder = gtk_builder_new_from_resource ("/org/gtk/gnoridor/resources/ui/action-popover.ui");
	self->actions = GTK_WIDGET (gtk_builder_get_object (self->builder, "player_actions"));
	return self;
}

GnoridorPlayer *
gnoridor_player_new_with_color (int color) {
	GnoridorPlayer *self = gnoridor_player_new ();
	gnoridor_player_set_color (self, color);
	return self;
}

void
gnoridor_player_move_to (GnoridorPlayer *self, GnoridorCell *cell)
{
	gtk_popover_set_relative_to (GTK_POPOVER (self->actions), GTK_WIDGET (cell));
}

void
gnoridor_player_color (GnoridorPlayer *self, cairo_t *cr) {
	cairo_set_source_rgb (cr,
						  self->color.r,
						  self->color.g,
						  self->color.b);
}

void
gnoridor_player_set_color (GnoridorPlayer *self, int color) {
	if (color == BLUE)
	{
		self->color.r = 0.3;
	 	self->color.g = 0.4;
		self->color.b = 0.6;
	}
	else if (color == RED)
	{
		self->color.r = 1.0;
	 	self->color.g = 0.0;
		self->color.b = 0.0;
	}
	else
	{
		self->color.r = 0.0;
	 	self->color.g = 0.0;
		self->color.b = 0.0;
	}
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
