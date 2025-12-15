/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:40:45 by miricci           #+#    #+#             */
/*   Updated: 2025/12/15 15:05:53 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wong_kar_wai.h"

volatile sig_atomic_t g_porcodio = 0;

void handle_resize(int sig) {
	(void)sig;
    g_porcodio = 1;
}

void	exit_game(void)
{
	printf("USCENDO...\n");
	ft_malloc(0, true);
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
			data->grid[i][j].value = 0;
			box(data->grid[i][j].win, 0, 0);
			curr_x += SQUARE_W; 
		}
		curr_y += SQUARE_H;
		curr_x = data->grid_pos_x;
	}
	return (true);
}

bool	init_all_windows(t_data *data)
{
	if (!init_game_windows(data))
		return (false);
	
	data->title = newwin(5, data->full_w, 0, 0);
	box(data->title, 0, 0);
	data->score = newwin(data->grid_size * SQUARE_H, data->full_w - (data->grid_pos_x + data->grid_win_w), 5, (data->grid_pos_x + data->grid_win_w));
	box(data->score, 0, 0);
	data->instruction = newwin(data->grid_size * SQUARE_H, data->grid_pos_x, 5, 0);
	box(data->instruction, 0, 0);

	return (true);
}
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
			box(data->grid[i][j].win, 0, 0);
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

	wresize(data->title, 5, data->full_w - 1);
	mvwin(data->title, 0, 0);
	werase(data->title);
	box(data->title, 0, 0);

	wresize(data->score, data->grid_win_h, data->full_w - (data->grid_pos_x + data->grid_win_w) - 1);
	mvwin(data->score, 5, (data->grid_pos_x + data->grid_win_w));
	werase(data->score);
	box(data->score, 0, 0);

	wresize(data->instruction, data->grid_size * SQUARE_H, data->grid_pos_x);
	mvwin(data->instruction, 5, 0);
	werase(data->instruction);
	box(data->instruction, 0, 0);

	return (true);
}


int	main(void)
{
	int	c;
	t_data	data;
	data = (t_data){0};
	data.log = open("log.txt", O_WRONLY);
	if (data.log <  0)
	{
		perror("");
		return 0;
	}
	
	initscr();
	// raw();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, data.full_h, data.full_w);

	mvprintw(0, 0, "Premi INVIO per iniziare\n");
	c = getch();

	data.full_h = LINES;
	data.full_w = COLS;

	if (!init_all_windows(&data))
		exit_game();
	
	while (1)
	{
		if (c == KEY_RESIZE)
		{
			write(data.log, "RESIZE CHIAMATO\n", 17);
			resize_all_windows(&data);
		}
		// TITLE
		mvwprintw(data.title, 2, ((data.full_w - ft_strlen(TITLE)) / 2) , TITLE);
		wnoutrefresh(data.title);
		// INSTRUCTIONS
		mvwprintw(data.instruction, 2, 2, "LALALALA");
		wnoutrefresh(data.instruction);
		// SCORE
		mvwprintw(data.score, 2, 2, "YOUR SCORE");
		wnoutrefresh(data.score);
		// GRID
		for (int i = 0; i < data.grid_size; i++)
		{
			for (int j = 0; j < data.grid_size; j++)
			{
				mvwprintw(data.grid[i][j].win, 2, 2, "%d", data.grid[i][j].value);
				wnoutrefresh(data.grid[i][j].win);
			}
		}
		
		doupdate();
		c = getch();
		if (c == 27)
			break ;
	}
	
	endwin();
}