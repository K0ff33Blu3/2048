/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:51:01 by miricci           #+#    #+#             */
/*   Updated: 2025/12/16 17:16:13 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wong_kar_wai.h"

void	restart_game(t_data *data)
{
	for (int i = 0; i < data->grid_size; i++)
	{
		for (int j = 0; j < data->grid_size; j++)
			data->grid[i][j].value = 0;
	}
	new_tile(data);
	new_tile(data);
}

void	you_lost(t_data data)
{
	WINDOW *lose_win;
	int	c;

	lose_win = newwin(data.full_h / 2, data.full_w / 2, (data.full_h - (data.full_h / 2)) / 2, (data.full_w - (data.full_w / 2)) / 2);
	waddstr(lose_win, "YOU LOST\n");
	waddstr(lose_win, "Press ESC to close game\n");
	waddstr(lose_win, "Press anything to play again\n");	
	c = wgetch(lose_win);
	delwin(lose_win);
	if (c == KEY_EXIT)
		return (exit_game());
	else
		return (restart_game(&data));
}

bool	new_tile(t_data *data)
{
	int	non_active_tile;
	int	rand_tile, rand_value;
	int	counter = 0;
	int	i = 0;
	int	j = 0;

	if (!data->moved)
		return (true);
	
	non_active_tile = 0;
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = 0; j < data->grid_size; j++) {
			if (!data->grid[i][j].value)
				non_active_tile++;
		}
	}
	if (non_active_tile == 0)
		return (you_lost(*data), false);
	rand_tile = rand() % non_active_tile;
	while (counter <= rand_tile)
	{
		if (j >= data->grid_size)
		{
			j = 0;
			i++;
		}
		else
			j++;
		if (data->grid[i][j].value == 0)
			counter++;
	}
	rand_value = rand() % 3;
	if (rand_value == 0)
		data->grid[i][j].value = 2;
	else if (rand_value == 1)
		data->grid[i][j].value = 2;
	else if (rand_value == 2)
		data->grid[i][j].value = 4;
	return (true);
}


/*
** Sposta tutte le celle verso sinistra, riempiendo gli spazi vuoti.
** Per ogni cella non vuota, la sposta verso sinistra finché non trova
** una cella occupata o raggiunge il bordo sinistro della griglia.
*/
void	swipe_left(t_data *data)
{
	int	k;
	
	data->moved = false;
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = 1; j < data->grid_size; j++) {
			k = j;
			if (data->grid[i][k].value == 0)
				continue ;
			while (k > 0 && (data->grid[i][k - 1].value == 0 || data->grid[i][k].value == data->grid[i][k - 1].value))
			{
				if (data->grid[i][k].flag == true)
					break ;
				check_and_swap(&data->grid[i][k], &data->grid[i][k - 1], data);
				k--;
			}
		}
	}
}

void	swipe_right(t_data *data)
{
	int	k;
	
	data->moved = false;
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = data->grid_size - 2; j >= 0; j--) {
			k = j;
			if (data->grid[i][j].value == 0)
				continue ;
			while (k < data->grid_size - 1 && (data->grid[i][k + 1].value == 0 || data->grid[i][k].value == data->grid[i][k + 1].value))
			{
				if (data->grid[i][k].flag == true)
					break ;
				check_and_swap(&data->grid[i][k], &data->grid[i][k + 1], data);
				k++;
			}
		}
	}
}

void	swipe_down(t_data *data)
{
	int	k;
	
	data->moved = false;
	for (int j = 0; j < data->grid_size; j++) {
		for (int i = data->grid_size - 2; i >= 0; i--) {
			k = i;
			if (data->grid[k][j].value == 0)
				continue ;
			while (k < data->grid_size - 1 && (data->grid[k + 1][j].value == 0 || data->grid[k][j].value == data->grid[k + 1][j].value))
			{
				if (data->grid[k][j].flag == true)
					break ;
				check_and_swap(&data->grid[k][j], &data->grid[k + 1][j], data);
				k++;
			}
		}
	}
}

void	check_and_swap(t_tile *curr, t_tile *new, t_data *data)
{
	if (new->value != 0)
		new->flag = true;
	new->value += curr->value;
	curr->value = 0;
	data->moved = true;
}

void	swipe_up(t_data *data)
{
	int	k;
	
	data->moved = false;
	for (int j = 0; j < data->grid_size; j++) {
		for (int i = 1; i < data->grid_size; i++) {
			k = i;
			if (data->grid[k][j].value == 0)
				continue ;
			while (k > 0 && (data->grid[k - 1][j].value == 0 || data->grid[k][j].value == data->grid[k - 1][j].value))
			{
				if (data->grid[k][j].flag == true)
					break ;
				check_and_swap(&data->grid[k][j], &data->grid[k - 1][j], data);
				k--;
			}
		}
	}
}
