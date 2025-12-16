/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:40:45 by miricci           #+#    #+#             */
/*   Updated: 2025/12/15 15:05:53 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wong_kar_wai.h"

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

	while (1)
	{
		if (c == KEY_RESIZE)
			resize_all_windows(&data);
		
		render(&data);
		c = getch();
		if (c == 27)
			break ;
	}
	
	endwin();
}

// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html