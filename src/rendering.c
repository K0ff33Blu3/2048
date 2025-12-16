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

void	render(t_data *data)
{
	clear();
	refresh();

	render_window(data->title, 2, ((data->full_w - ft_strlen(TITLE)) / 2), TITLE, BLACK);
	render_window(data->instruction, 2, 2, "LALALALA", BLACK);
	render_window(data->score, 2, 2,  "YOUR SCORE", BLACK);

	for (int i = 0; i < data->grid_size; i++)
	{
		for (int j = 0; j < data->grid_size; j++)
			render_tile(&data->grid[i][j]);
	}
	doupdate();
}