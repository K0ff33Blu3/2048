#include "wong_kar_wai.h"

bool	init_game_windows(t_data *data)
{	
	data->grid_size = 4;
	data->grid_win_w = SQUARE_W * data->grid_size;
	data->grid_win_h = SQUARE_H * data->grid_size;
	data->grid_pos_x = (data->full_w / 2) - (data->grid_win_w / 2);
	data->grid_pos_y = 5;
	int curr_x = data->grid_pos_x;
	int curr_y = data->grid_pos_y;
	
	data->grid = ft_malloc(sizeof(t_tile *) * data->grid_size, false);
	if (data->grid == NULL)
		return (false);
	
	for (int i = 0; i < data->grid_size; i++)
	{
		data->grid[i] = ft_malloc(sizeof(t_tile) * data->grid_size, false);
		if (data->grid[i] == NULL)
			return (false);
		for (int j = 0; j < data->grid_size; j++)
		{
			data->grid[i][j].win = newwin(SQUARE_H, SQUARE_W, curr_y, curr_x);
			wbkgd(data->grid[i][j].win, COLOR_PAIR(GOTTO));
			data->grid[i][j].value = 0;
			curr_x += SQUARE_W; 
		}
		curr_y += SQUARE_H;
		curr_x = data->grid_pos_x;
	}
	return (true);
}

void	init_my_colors()
{
	init_pair(1, COLOR_YELLOW, COLOR_CYAN); // GOTTO
	init_pair(2, COLOR_BLACK, COLOR_MAGENTA); // EUH
	init_pair(3, COLOR_WHITE, COLOR_GREEN); // BOH

	init_pair(4, COLOR_WHITE, COLOR_WHITE); // WHITE
}

bool	init_all_windows(t_data *data)
{
	init_my_colors();
	wbkgd(stdscr, COLOR_PAIR(WHITE));

	if (!init_game_windows(data))
		return (false);
	
	data->title = newwin(5, data->full_w, 0, 0);
	wbkgd(data->title, COLOR_PAIR(EUH));

	data->score = newwin(data->grid_size * SQUARE_H, data->full_w - (data->grid_pos_x + data->grid_win_w), 5, (data->grid_pos_x + data->grid_win_w));
	wbkgd(data->score, COLOR_PAIR(EUH));

	data->instruction = newwin(data->grid_size * SQUARE_H, data->grid_pos_x, 5, 0);
	wbkgd(data->instruction, COLOR_PAIR(BOH));

	return (true);
}

bool	init_data(t_data *data)
{
	*data = (t_data){0};
	data->log = open("log.txt", O_WRONLY);
	if (data->log <  0)
	{
		perror("");
		return false;
	}
	
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	start_color();
	getmaxyx(stdscr, data->full_h, data->full_w);
	if (!init_all_windows(data))
		return (false);
    
	return (true);
}