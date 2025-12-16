#include "wong_kar_wai.h"

void	exit_game(void)
{
	ft_malloc(0, true);
	exit(1);
}

void	my_box(WINDOW *win, int color)
{
	wattron(win, COLOR_PAIR(color));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(color));
}