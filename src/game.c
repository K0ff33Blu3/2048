/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:51:01 by miricci           #+#    #+#             */
/*   Updated: 2025/12/15 19:20:52 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wong_kar_wai.h"

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
	ft_putstr_fd("\nnon_active_tile: ", 2);
	ft_putnbr_fd(non_active_tile, 2);
	rand_tile = rand() % non_active_tile;
	ft_putstr_fd("\nrand_tile: ", 2);
	ft_putnbr_fd(rand_tile, 2);
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
	ft_putstr_fd("\nrow i: ", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("\ncol j: ", 2);
	ft_putnbr_fd(j, 2);
	ft_putstr_fd("\nrand_value: ", 2);
	ft_putnbr_fd(rand_value, 2);
	if (rand_value == 0)
		data->grid[i][j].value = 2;
	else if (rand_value == 1)
		data->grid[i][j].value = 4;
}

/*
** Somma le celle adiacenti con lo stesso valore spostandosi verso sinistra.
** Itera ogni riga saltando una cella alla volta (j += 2) per evitare
** di sommare la stessa cella due volte. Se la cella a sinistra è vuota
** o ha lo stesso valore, somma i valori e azzera la cella corrente.
*/
void	sum_left(t_data *data)
{
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = 1; j < data->grid_size; j += 2) {
			if (data->grid[i][j].value == data->grid[i][j - 1].value)
			{
				data->grid[i][j - 1].value += data->grid[i][j].value;
				data->grid[i][j].value = 0;
			}
		}
	}
	// for (int i = 0; i < data->grid_size; i++)
	// {
	// 	for (int j = 0; j < data->grid_size; j++)
	// 	{
	// 		if (data->grid[i][j].value)
	// 			mvwprintw(data->grid[i][j].win, 2, 2, "%d", data->grid[i][j].value);
	// 		wnoutrefresh(data->grid[i][j].win);
	// 	}
	// }
}

/*
** Sposta tutte le celle verso sinistra, riempiendo gli spazi vuoti.
** Per ogni cella non vuota, la sposta verso sinistra finché non trova
** una cella occupata o raggiunge il bordo sinistro della griglia.
*/
void	swipe_left(t_data *data)
{
	int	k;
	int	temp;
	
	for (int i = 0; i < data->grid_size; i++) {
		for (int j = 1; j < data->grid_size; j++) {
			k = j;
			if (data->grid[i][j].value == 0)
				continue ;
			temp = data->grid[i][j].value;
			while (k > 0 && data->grid[i][k - 1].value == 0)
			{
				data->grid[i][k - 1].value = data->grid[i][j].value;
				data->grid[i][k].value = 0;
				k--;
			}
		}
	}
}
