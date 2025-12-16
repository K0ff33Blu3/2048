#include "wong_kar_wai.h"

void	free_data(t_data *data)
{
	for (int i = 0; i < data->grid_size; i++)
	{
		for (int j = 0; j < data->grid_size; j++)
		{
			delwin(data->grid[i][j].win);
		}
		free(data->grid[i]);
	}
	free(data->grid);
	free(data->best_score);
	delwin(data->title);
	delwin(data->score);
	delwin(data->instruction);
	delwin(data->end_screen);
	delwin(data->menu);
}

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