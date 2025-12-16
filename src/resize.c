#include "wong_kar_wai.h"

bool	resize_grid(t_data *data)
{
	data->grid_pos_x = (data->full_w / 2) - (data->grid_win_w / 2);
	data->grid_pos_y = 5;
	int curr_x = data->grid_pos_x;
	int curr_y = data->grid_pos_y;

	for (int i = 0; i < data->grid_size; i++)
	{
		for (int j = 0; j < data->grid_size; j++)
		{
			if (wresize(data->grid[i][j].win, SQUARE_H, SQUARE_W) == ERR)
				ft_putstr_fd("fallito resize in grid", data->log);

			mvwin(data->grid[i][j].win, curr_y, curr_x);
			werase(data->grid[i][j].win);
			curr_x += SQUARE_W;
		}
		curr_y += SQUARE_H;
		curr_x = data->grid_pos_x;
	}
	return (true);
}

bool	resize_all_windows(t_data *data)
{
	getmaxyx(stdscr, data->full_h, data->full_w);
	
	resize_grid(data);

	wclear(data->title);
	wresize(data->title, 5, data->full_w - 1);
	mvwin(data->title, 0, 0);

	wclear(data->score);
	wresize(data->score, data->grid_win_h, data->full_w - (data->grid_pos_x + data->grid_win_w) - 1);
	mvwin(data->score, 5, (data->grid_pos_x + data->grid_win_w));

	wclear(data->instruction);
	wresize(data->instruction, data->grid_size * SQUARE_H, data->grid_pos_x);
	mvwin(data->instruction, 5, 0);

	wclear(data->end_screen);
	wresize(data->end_screen, data->full_h / 2, data->full_w / 2);
	mvwin(data->end_screen, (data->full_h - (data->full_h / 2)) / 2, (data->full_w - (data->full_w / 2)) / 2);

	clear();

	return (true);
}
