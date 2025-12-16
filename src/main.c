/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:40:45 by miricci           #+#    #+#             */
/*   Updated: 2025/12/16 15:33:49 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wong_kar_wai.h"

void	handle_menu_keys(t_data *data, int c)
{
	if (c == KEY_RESIZE)
		resize_all_windows(data);
	else if (c == 52)
	{
		data->grid_size = 4;
		data->in_menu = false;
		init_in_game_windows(data);
	}
	else if (c == 53)
	{
		data->grid_size = 5;
		data->in_menu = false;
		init_in_game_windows(data);
	}
}

void	handle_win_loss_keys(t_data *data, int c)
{
	if (c == KEY_RESIZE)
		resize_all_windows(data);
	else if (data->lost && c == 'r')
		restart_game(data);
	else if (data->won && c == 'c')
		data->won = false;
}

void	handle_input(t_data *data, int c)
{
	if (c == 27)
	{
		// ft_putstr_fd("Uscendo\n", data->log);
		exit_game(data);
		return ;
	}

	if (data->in_menu)
		return (handle_menu_keys(data, c));

	if (data->lost || data->won)
		return (handle_win_loss_keys(data, c));
	
	else if (c == KEY_UP)
	{
		swipe_up(data);
		new_tile(data);
	}
	else if (c == KEY_DOWN)
	{
		swipe_down(data);
		new_tile(data);
	}
	else if (c == KEY_LEFT)
	{
		swipe_left(data);
		new_tile(data);
	}
	else if (c == KEY_RIGHT)
	{
		swipe_right(data);
		new_tile(data);
	}
	else if (c == KEY_RESIZE)
			resize_all_windows(data);
}

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

int	main(void)
{
	int	c;
	t_data	data;
	
	if (!init_data(&data))
		exit_game(&data);
	// print_map(data, data.log);
	while (!data.end)
	{
		render(&data);
		// print_map(data, data.log);
		c = getch();
		handle_input(&data, c);
	}

	free_data(&data);
	endwin();
}

// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html