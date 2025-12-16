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
	data->moved = true;
	data->lost = false;
	new_tile(data);
	new_tile(data);
	clear();
}

bool	new_tile(t_data *data)
{
	int	non_active_tile;
	int	rand_tile, rand_value;
	int	counter = 0;
	int	i = 0;
	int	j = 0;

	
	non_active_tile = 0;
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = 0; j < data->grid_size; j++) {
			if (!data->grid[i][j].value)
			non_active_tile++;
		}
	}
	if (non_active_tile == 0)
	{
		data->lost = true;
		return (false);
	}
	if (!data->moved)
		return (true);
	rand_tile = rand() % non_active_tile;
	while (i < data->grid_size)
	{
	    if (data->grid[i][j].value == 0)
	    {
	        if (counter == rand_tile)
	            break;
	        counter++;
	    }
	    j++;
	    if (j == data->grid_size)
	    {
	        j = 0;
	        i++;
	    }
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

void	check_and_swap(t_tile *curr, t_tile *new, t_data *data)
{
	if (new->value != 0)
		new->flag = true;
	new->value += curr->value;
	if (new->value == WIN_VALUE && !data->already_won)
		data->won = true;
	if (new->value > ft_atoi(data->best_score))
	{
		free(data->best_score);
		data->best_score = ft_itoa(new->value);
		close(data->score_fd);
		data->score_fd = open(".score", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->score_fd > 0)
			write(data->score_fd, data->best_score, ft_strlen(data->best_score));
	}
	curr->value = 0;
	data->moved = true;
}

void	swipe_left(t_data *data)
{
	int	k = 0;
	
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
	int	k = 0;
	
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
	int	k = 0;
	
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


void	swipe_up(t_data *data)
{
	int	k = 0;
	
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
