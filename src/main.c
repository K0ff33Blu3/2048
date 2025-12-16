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

int	main(void)
{
	int	c;
	t_data	data;
	
	if (!init_data(&data))
		exit_game(&data);
	// print_map(data, data.log);
	while (!data.end)
	{
		render(&data);
		// print_map(data, data.log);
		c = getch();
		handle_input(&data, c);
	}

	free_data(&data);
	endwin();
}

// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html