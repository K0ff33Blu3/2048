/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wong_kar_wai.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:39:07 by miricci           #+#    #+#             */
/*   Updated: 2025/12/15 14:52:33 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WONG_KAR_WAI_H
# define WONG_KAR_WAI_H

# include <ncurses.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

#define GAME_X 8
#define GAME_Y 8
#define SQUARE_W 8
#define SQUARE_H 5


typedef struct s_tile
{
	int		value;
	WINDOW	*win;
}			t_tile;

typedef struct s_data
{
	int		grid_size;
	t_tile	**grid;
	WINDOW	*title;
	WINDOW	*score;
	// WINDOW	*instruction
} 			t_data;

bool	init_game_windows(t_data *data);
void	cleaning(t_list **lis);
void	*ft_malloc(size_t size, bool CLEAN);

#endif