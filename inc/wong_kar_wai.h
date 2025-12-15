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
# include <signal.h>
# include "libft.h"

#define GAME_X 8
#define GAME_Y 5
#define SQUARE_W 8
#define SQUARE_H 5

#define TITLE "2048 in the 2025"

extern volatile sig_atomic_t g_porcodio;


typedef struct s_tile
{
	int		value;
	WINDOW	*win;
}			t_tile;

typedef struct s_data
{
	int		log;

	int		full_w;
	int		full_h;

	int		grid_size;
	int		grid_win_w;
	int		grid_win_h;
	int		grid_pos_x;
	int		grid_pos_y;
	t_tile	**grid;

	int		title_win_w;
	int		title_win_h;
	WINDOW	*title;
	WINDOW	*score;
	WINDOW	*instruction;
} 			t_data;

bool	init_game_windows(t_data *data);
void	cleaning(t_list **lis);
void	*ft_malloc(size_t size, bool CLEAN);

#endif