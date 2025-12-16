#include "wong_kar_wai.h"

void	print_map(t_data data, int fd)
{
	for (int i = 0; i < data.grid_size; i++)
	{
		for (int j = 0; j < data.grid_size; j++)
		{
			ft_putnbr_fd(data.grid[i][j].value, fd);
			ft_putchar_fd(' ', fd);
		}
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\n', fd);
}

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
	new_tile(data);
	new_tile(data);
	return (true);
}

void	init_my_colors()
{
	init_pair(1, COLOR_YELLOW, COLOR_CYAN); // GOTTO
	init_pair(2, COLOR_BLACK, COLOR_MAGENTA); // EUH
	init_pair(3, COLOR_WHITE, COLOR_GREEN); // BOH
	init_pair(4, COLOR_WHITE, COLOR_WHITE); // WHITE
	
	init_pair(5, COLOR_BLACK, COLOR_RED); // 4
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA); // 8
	init_pair(7, COLOR_BLACK, COLOR_BLUE); // 16
	init_pair(8, COLOR_BLACK, COLOR_CYAN); // 32
	init_pair(9, COLOR_BLACK, COLOR_GREEN); // 64
	init_pair(10, COLOR_BLACK, COLOR_YELLOW); // TWO

	init_pair(11, COLOR_BLACK, COLOR_BLACK); // BLACK
}

bool	init_all_windows(t_data *data)
{
	init_my_colors();
	wbkgd(stdscr, COLOR_PAIR(BLACK));
	srand((unsigned int)time(NULL));

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
	data->moved = true;
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