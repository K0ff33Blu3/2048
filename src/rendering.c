#include "wong_kar_wai.h"

static void render_window(WINDOW *win, int txt_y, int txt_x, const char *txt, int box_color)
{
    mvwaddstr(win, txt_y, txt_x, txt);
    if (box_color >= 0)
        my_box(win, box_color);
    wnoutrefresh(win);
}

void	render(t_data *data)
{
	clear();
	refresh();

    render_window(data->title, 2, ((data->full_w - ft_strlen(TITLE)) / 2), TITLE, WHITE);
    render_window(data->instruction, 2, 2, "LALALALA", WHITE);
    render_window(data->score, 2, 2,  "YOUR SCORE", WHITE);

	for (int i = 0; i < data->grid_size; i++)
	{
		for (int j = 0; j < data->grid_size; j++)
		{
            char *nbr = ft_itoa(data->grid[i][j].value);
            render_window(data->grid[i][j].win, (SQUARE_H / 2) , ((SQUARE_W - ft_strlen(nbr)) / 2), nbr, -1);
		}
	}
	
	doupdate();
}