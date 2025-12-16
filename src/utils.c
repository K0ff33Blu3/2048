#include "wong_kar_wai.h"

void	exit_game(t_data *data)
{
	data->end = true;
}

void	my_box(WINDOW *win, int color)
{
	wattron(win, COLOR_PAIR(color));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(color));
}