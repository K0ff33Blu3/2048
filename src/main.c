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

void	handle_input(t_data *data, int c)
{
	if (c == KEY_EXIT)
		exit_game();
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

int	main(void)
{
	int	c;
	t_data	data;
	
	if (!init_data(&data))
		exit_game();

	attron(COLOR_PAIR(GOTTO));
	mvprintw(0, 0, "Premi INVIO per iniziare\n");
	attroff(COLOR_PAIR(GOTTO));
	c = getch();
	clear();
	refresh();
	print_map(data, data.log);
	while (1)
	{
		handle_input(&data, c);
		render(&data);
		print_map(data, data.log);
		c = getch();
	}
	endwin();
}

// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html