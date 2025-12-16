#include "wong_kar_wai.h"

static int		get_color_pair(int value)
{
	switch (value)
	{
		case 0:
			return (WHITE);
		case 2:
			return (TWO);
		case 4:
			return (FOUR);
		case 8:
			return (EIGHT);
		case 16:
			return (SIXT);
		case 32:
			return (THRTWO);
		case 64:
			return (SIXFOUR);
		default:
			return (GOTTO);
	}
	return (GOTTO);
}

static void	render_tile(t_tile *tile)
{
	int pair = get_color_pair(tile->value);

	wbkgd(tile->win, COLOR_PAIR(pair));
	werase(tile->win);
	my_box(tile->win, BLACK);

	char *nbr = ft_itoa(tile->value);
	mvwaddstr(tile->win, SQUARE_H / 2, (SQUARE_W - ft_strlen(nbr)) / 2, nbr);
	tile->flag = false;
	free(nbr);
	wnoutrefresh(tile->win);
}

static void render_window(WINDOW *win, int txt_y, int txt_x, const char *txt, int box_color)
{
	werase(win);
    mvwaddstr(win, txt_y, txt_x, txt);
    if (box_color >= 0)
        my_box(win, box_color);
    wnoutrefresh(win);
}

static void	render_end_screen(t_data *data)
{
	werase(data->end_screen);
	if (data->lost)
	{
		mvwaddstr(data->end_screen, 3,(((data->full_w / 2) - ft_strlen("YOU LOST")) / 2), "YOU LOST");
		mvwaddstr(data->end_screen, 6,(((data->full_w / 2)  - ft_strlen("Press ESC to close game")) / 2), "Press ESC to close game");
		mvwaddstr(data->end_screen, 7,(((data->full_w / 2)  - ft_strlen("Press r to play again")) / 2), "Press r to play again");
	}
	else
	{
		mvwaddstr(data->end_screen, 3,(((data->full_w / 2) - ft_strlen("YOU WON")) / 2), "YOU WON");
		mvwaddstr(data->end_screen, 6,(((data->full_w / 2)  - ft_strlen("Press ESC to close game")) / 2), "Press ESC to close game");
		mvwaddstr(data->end_screen, 7,(((data->full_w / 2)  - ft_strlen("Press c to continue playing")) / 2), "Press c to continue playing");
	}
	box(data->end_screen, 0, 0);
	wnoutrefresh(data->end_screen);
}

static	void render_instruction(t_data *data)
{
	WINDOW *win = data->instruction;

	werase(win);

    mvwaddstr(win, 2, 2, "INSTRUCTIONS");
    mvwaddstr(win, 5, 2, "UP, DOWN, LEFT and RIGHT arrows");
    mvwaddstr(win, 6, 2, "to move and merge");
    mvwaddstr(win, 8, 2, "ESC to close game");

    my_box(win, BLACK);
    wnoutrefresh(win);
}

static void	render_score(t_data *data)
{
	werase(data->score);
    mvwaddstr(data->score, 2, 2, "BEST SCORE");
	mvwaddstr(data->score, 4, 2, data->best_score);

	my_box(data->score, BLACK);
	wnoutrefresh(data->score);
}

static void render_menu(t_data *data)
{
	werase(data->menu);
	mvwaddstr(data->menu, 3, (data->full_w - ft_strlen("MENU")) / 2, "MENU");
	mvwaddstr(data->menu, data->full_h / 2, (data->full_w - ft_strlen("Press 4 to play 4x4         Press 5 to play 5x5")) / 2, "Press 4 to play 4x4         Press 5 to play 5x5");
	box(data->menu, 0, 0);
	wnoutrefresh(data->menu);
}

void	render(t_data *data)
{
	refresh();

	if (data->in_menu)
		render_menu(data);
	else
	{
		render_window(data->title, 2, ((data->full_w - ft_strlen(TITLE)) / 2), TITLE, BLACK);
		render_instruction(data);
		render_score(data);
		
		for (int i = 0; i < data->grid_size; i++)
		{
			for (int j = 0; j < data->grid_size; j++)
				render_tile(&data->grid[i][j]);
		}
	
		if (data->lost || data->won)
			render_end_screen(data);
	}

	doupdate();
}