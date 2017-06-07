#include "gnoridor-player.h"
#include "gnoridor-cell.h"
#include "callback.h"

G_DEFINE_TYPE (GnoridorPlayer, gnoridor_player, GTK_TYPE_WIDGET)

GnoridorPlayer *
gnoridor_player_new (void)
{
	GnoridorPlayer *self = g_object_new (GNORIDOR_TYPE_PLAYER, NULL);
	self->builder = gtk_builder_new_from_resource ("/org/gtk/gnoridor/src/resources/ui/action-popover.ui");
	self->actions = GTK_WIDGET (gtk_builder_get_object (self->builder, "player_actions"));

	// Get buttons from builder
	GtkButton *up_bt = GTK_BUTTON (gtk_builder_get_object (self->builder, "up_b"));
	GtkButton *down_bt = GTK_BUTTON (gtk_builder_get_object (self->builder, "down_b"));
	GtkButton *left_bt = GTK_BUTTON (gtk_builder_get_object (self->builder, "left_b"));
	GtkButton *right_bt = GTK_BUTTON (gtk_builder_get_object (self->builder, "right_b"));

	// Connect them to their respective signals
	g_signal_connect (G_OBJECT (up_bt), "clicked",
					  G_CALLBACK (up_button_callback), self);
	g_signal_connect (G_OBJECT (down_bt), "clicked",
				  	  G_CALLBACK (down_button_callback), self);
	g_signal_connect (G_OBJECT (left_bt), "clicked",
				      G_CALLBACK (left_button_callback), self);
	g_signal_connect (G_OBJECT (right_bt), "clicked",
				      G_CALLBACK (right_button_callback), self);

	return self;
}

GnoridorPlayer *
gnoridor_player_new_with_color (int color) {
	GnoridorPlayer *self = gnoridor_player_new ();
	self->id = color;
	gnoridor_player_set_color (self, color);
        gnoridor_player_color_int_to_char(self);
	return self;
}

static void
gnoridor_player_init (GnoridorPlayer *self)
{
	self->number_of_walls = 0;
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
	G_OBJECT_CLASS (gnoridor_player_parent_class)->finalize (object);
}

static void
gnoridor_player_class_init (GnoridorPlayerClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	object_class->finalize = gnoridor_player_finalize;
}


void
gnoridor_player_color_int_to_char (GnoridorPlayer *self)
{
    switch (self->id) {
        case BLUE:
            sprintf(self->name, "Blue");
            break;
        case RED:
            sprintf(self->name, "Red");
            break;
        default:
            sprintf(self->name, "Err");
            break;
    }

}
