#include "wong_kar_wai.h"

void	handle_menu_keys(t_data *data, int c)
{
	if (c == KEY_RESIZE)
		resize_all_windows(data);
	else if (c == 52)
	{
		data->grid_size = 4;
		data->in_menu = false;
		init_in_game_windows(data);
	}
	else if (c == 53)
	{
		data->grid_size = 5;
		data->in_menu = false;
		init_in_game_windows(data);
	}
}

void	handle_win_loss_keys(t_data *data, int c)
{
	if (c == KEY_RESIZE)
		resize_all_windows(data);
	else if (data->lost && c == 'r')
		restart_game(data);
	else if (data->won && c == 'c')
    {
		data->won = false;
        data->already_won = true;
    }
}

void	handle_input(t_data *data, int c)
{
	if (c == 27)
	{
		// ft_putstr_fd("Uscendo\n", data->log);
		exit_game(data);
		return ;
	}

	if (data->in_menu)
		return (handle_menu_keys(data, c));

	if (data->lost || data->won)
		return (handle_win_loss_keys(data, c));
	
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