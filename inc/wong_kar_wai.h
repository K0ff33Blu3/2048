/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wong_kar_wai.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:39:07 by miricci           #+#    #+#             */
/*   Updated: 2025/12/16 17:20:47 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WONG_KAR_WAI_H
# define WONG_KAR_WAI_H

# include <ncurses.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <time.h>
# include "libft.h"

#define GAME_X 8
#define GAME_Y 5
#define SQUARE_W 11
#define SQUARE_H 7

#define TITLE "2048 in 2025"
#define GOTTO 1
#define EUH 2
#define BOH 3
#define WHITE 4
#define BLACK 11

#define TWO 10
#define FOUR 5
#define EIGHT 6
#define SIXT 7
#define THRTWO 8
#define SIXFOUR 9

enum e_const
{
	WIN_VALUE = 4
};

typedef struct s_tile
{
	int		value;
	bool	flag;
	WINDOW	*win;
}			t_tile;

typedef struct s_data
{
	char	*best_score;
	int		score_fd;
	int		log;
	bool	moved;
	bool	lost;
	bool	won;
	bool	already_won;
	bool	in_menu;
	bool	end;

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
	WINDOW	*end_screen;
	WINDOW	*menu;

} 			t_data;



// inits.c
bool	init_data(t_data *data);
bool	init_all_windows(t_data *data);
void	init_my_colors();
bool 	init_in_game_windows(t_data *data);
bool	init_game_windows(t_data *data);

// resize.c
bool	resize_grid(t_data *data);
bool	resize_all_windows(t_data *data);

// rendering.c
void	render(t_data *data);

// utils.c
void	exit_game(t_data *data);
void	my_box(WINDOW *win, int color);
void	free_data(t_data *data);

// input_handler.c
void	handle_menu_keys(t_data *data, int c);
void	handle_win_loss_keys(t_data *data, int c);
void	handle_input(t_data *data, int c);

// game.c
bool	new_tile(t_data *data);
void	swipe_left(t_data *data);
void	swipe_right(t_data *data);
void	swipe_down(t_data *data);
void	swipe_up(t_data *data);
void	check_and_swap(t_tile *curr, t_tile *new, t_data *data);
void	restart_game(t_data *data);


// alloc_handler.c
void	cleaning(t_list **lis);
void	*ft_malloc(size_t size, bool CLEAN);
void	print_map(t_data data, int fd);

// valgrind --suppressions=ncurses.supp --leak-check=full --log-file=valgrind.log ./2048

#endif