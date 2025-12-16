/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:40:45 by miricci           #+#    #+#             */
/*   Updated: 2025/12/16 12:57:58 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wong_kar_wai.h"

void	exit_game(void)
{
	printf("USCENDO...\n");
	ft_malloc(0, true);
}

void	handle_input(t_data data, char c)
{
	if (c == 27)
		return ;
	else if (c == KEY_UP)
	{
		swipe_up(&data);
		new_tile(&data);
	}
	else if (c == KEY_DOWN)
	{
		swipe_down(&data);
		new_tile(&data);
	}
	else if (c == KEY_LEFT)
	{
		swipe_left(&data);
		new_tile(&data);
	}
	else if (c == KEY_RIGHT)
	{
		swipe_right(&data);
		new_tile(&data);
	}
}
bool	init_game_windows(t_data *data)
{	
	int curr_x = GAME_X;
	int curr_y = GAME_Y;
	
	data->grid_size = 4;
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
		curr_x = GAME_X;
	}
	return (true);
}

int	main(void)
{
	int	c;
	t_data	data;
	data = (t_data){0};
	
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	mvprintw(0, 0, "Premi INVIO per iniziare\n");
	c = getch();
	if (!init_game_windows(&data))
		exit_game();
	data.title = newwin(7, 50, 0, 0);
	box(data.title, 0, 0);
	data.score = newwin(data.grid_size * SQUARE_H, 15, 8, GAME_X + (data.grid_size * SQUARE_W));
	box(data.score, 0, 0);
	// TITLE
	mvwprintw(data.title, 2, 15, "2048 in the 2025");
	wnoutrefresh(data.title);
	// SCORE
	mvwprintw(data.score, 2, 2, "YOUR SCORE");
	wnoutrefresh(data.score);
	while (1)
	{
		// GRID refresh
		for (int i = 0; i < data.grid_size; i++)
		{
			for (int j = 0; j < data.grid_size; j++)
			{
				data.grid[i][j].flag = false;
				werase(data.grid[i][j].win);
				box(data.grid[i][j].win, 0, 0);
				if (data.grid[i][j].value)
					mvwprintw(data.grid[i][j].win, 2, 2, "%d", data.grid[i][j].value);
				wnoutrefresh(data.grid[i][j].win);
			}
		}
		doupdate();
		c = getch();
		handle_input(data, c);
	}
	endwin();
}