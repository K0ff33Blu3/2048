/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wong_kar_wai.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:39:07 by miricci           #+#    #+#             */
/*   Updated: 2025/12/15 22:48:16 by miricci          ###   ########.fr       */
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
#define SQUARE_W 11
#define SQUARE_H 7

#define TITLE "2048 in the 2025"
#define GOTTO 1
#define EUH 2
#define BOH 3
#define WHITE 4

typedef struct s_tile
{
	int		value;
	bool	flag;
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

	WINDOW	*title;
	WINDOW	*score;
	WINDOW	*instruction;
} 			t_data;



// inits.c
bool	init_data(t_data *data);
bool	init_all_windows(t_data *data);
void	init_my_colors();
bool	init_game_windows(t_data *data);

// resize.c
bool	resize_grid(t_data *data);
bool	resize_all_windows(t_data *data);

// rendering.c
void	render(t_data *data);

// utils.c
void	exit_game(void);
void	my_box(WINDOW *win, int color);

// alloc_handler.c
void	cleaning(t_list **lis);
void	*ft_malloc(size_t size, bool CLEAN);
void	new_tile(t_data *data);
void	swipe_left(t_data *data);
void	swipe_right(t_data *data);
void	swipe_down(t_data *data);
void	swipe_up(t_data *data);

#endif