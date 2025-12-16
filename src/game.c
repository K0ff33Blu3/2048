/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:51:01 by miricci           #+#    #+#             */
/*   Updated: 2025/12/15 22:55:00 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wong_kar_wai.h"

// void	you_lose()
// {
	
// }

void	new_tile(t_data *data)
{
	int	non_active_tile;
	int	rand_tile, rand_value;
	int	counter = 0;
	int	i = 0;
	int	j = -1;

	non_active_tile = 0;
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = 0; j < data->grid_size; j++) {
			if (!data->grid[i][j].value)
				non_active_tile++;
		}
	}
	// if (non_active_tile == 0)
	// 	you_lose();
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
	rand_value = rand() % 2;
	if (rand_value == 0)
		data->grid[i][j].value = 2;
	else if (rand_value == 1)
		data->grid[i][j].value = 4;
}


/*
** Sposta tutte le celle verso sinistra, riempiendo gli spazi vuoti.
** Per ogni cella non vuota, la sposta verso sinistra finché non trova
** una cella occupata o raggiunge il bordo sinistro della griglia.
*/
void	swipe_left(t_data *data)
{
	int	k;
	// int	temp;
	
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = 1; j < data->grid_size; j++) {
			k = j;
			if (data->grid[i][k].value == 0)
				continue ;
			// temp = data->grid[i][j].value;
			while (k > 0 && (data->grid[i][k - 1].value == 0 || data->grid[i][k].value == data->grid[i][k - 1].value))
			{
				if (data->grid[i][k].flag == true)
					break ;
				if (data->grid[i][k - 1].value != 0)
					data->grid[i][k - 1].flag = true;
				data->grid[i][k - 1].value += data->grid[i][k].value;
				data->grid[i][k].value = 0;
				k--;
			}
		}
	}
}

void	swipe_right(t_data *data)
{
	int	k;
	
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = data->grid_size - 2; j >= 0; j--) {
			k = j;
			if (data->grid[i][j].value == 0)
				continue ;
			while (k < data->grid_size - 1 && (data->grid[i][k + 1].value == 0 || data->grid[i][k].value == data->grid[i][k + 1].value))
			{
				if (data->grid[i][k].flag == true)
					break ;
				if (data->grid[i][k + 1].value != 0)
					data->grid[i][k + 1].flag = true;
				data->grid[i][k + 1].value += data->grid[i][k].value;
				data->grid[i][k].value = 0;
				k++;
			}
		}
	}
}

void	swipe_down(t_data *data)
{
	int	k;
	
	for (int j = 0; j < data->grid_size; j++) {
		for (int i = data->grid_size - 2; i >= 0; i--) {
			k = i;
			if (data->grid[k][j].value == 0)
				continue ;
			while (k < data->grid_size - 1 && (data->grid[k + 1][j].value == 0 || data->grid[k][j].value == data->grid[k + 1][j].value))
			{
				if (data->grid[k][j].flag == true)
					break ;
				if (data->grid[k + 1][j].value != 0)
					data->grid[k + 1][j].flag = true;
				data->grid[k + 1][j].value += data->grid[k][j].value;
				data->grid[k][j].value = 0;
				k++;
			}
		}
	}
}

void	swipe_up(t_data *data)
{
	int	k;
	
	for (int j = 0; j < data->grid_size; j++) {
		for (int i = 1; i < data->grid_size; i++) {
			k = i;
			if (data->grid[k][j].value == 0)
				continue ;
			while (k > 0 && (data->grid[k - 1][j].value == 0 || data->grid[k][j].value == data->grid[k - 1][j].value))
			{
				if (data->grid[k][j].flag == true)
					break ;
				if (data->grid[k - 1][j].value != 0)
					data->grid[k - 1][j].flag = true;
				data->grid[k - 1][j].value += data->grid[k][j].value;
				data->grid[k][j].value = 0;
				k--;
			}
		}
	}
}
