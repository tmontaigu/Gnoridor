#include "../src/gnoridor-board.h" // erk
#include "../src/gnoridor-cell.h" // erk
#include "../src/gnoridor-define.h"

#include <gtk/gtk.h>
#include <assert.h>

void
test_upper_bound()
{
	GnoridorBoard *board = gnoridor_board_new();
	GnoridorCell *cell;
	for (unsigned i = 0; i < NUMBER_OF_COLS; ++i)
	{
		cell = run_check_dir(board, board->cells[0][i], Up);
		assert(cell == NULL);
	}
}

void
test_lower_bound()
{
	GnoridorBoard *board = gnoridor_board_new();
	GnoridorCell *cell;
	for (unsigned i = 0; i < NUMBER_OF_COLS; ++i)
	{
		cell = run_check_dir(board, board->cells[NUMBER_OF_ROWS-1][i], Down);
		assert(cell == NULL);
	}
}

void
test_left_bound()
{
	GnoridorBoard *board = gnoridor_board_new();
	GnoridorCell *cell;
	for (unsigned i = 0; i < NUMBER_OF_ROWS; ++i)
	{
		cell = run_check_dir(board, board->cells[i][0], Left);
		assert(cell == NULL);
	}
}

void
test_right_bound()
{
	GnoridorBoard *board = gnoridor_board_new();
	GnoridorCell *cell;
	for (unsigned i = 0; i < NUMBER_OF_ROWS; ++i)
	{
		cell = run_check_dir(board, board->cells[i][NUMBER_OF_COLS-1], Right);
		assert(cell == NULL);
	}
}


static int
activate (GtkApplication *app,
          gpointer       user_data)
{

	test_upper_bound();
	test_lower_bound();
	test_left_bound();
	test_right_bound();
	return 0;
}


int main(int   argc,
		 char *argv[])
{
	g_autoptr(GtkApplication) app = NULL;
	int status;

	app = gtk_application_new ("org.gnome.Gnoridor", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);

	return status;
}
