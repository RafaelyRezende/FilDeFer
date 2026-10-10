#include "iso_fdf.h"

/*
** P-05 fix: all-octant integer Bresenham. Endpoints are rounded once to
** integer screen coordinates; the walk itself uses only integer adds and
** comparisons, eliminating the float mutation + fabs() > 0.5f loop tests
** (and their accumulated rounding error) of the previous implementation.
** Color is interpolated along the dominant axis step count.
*/
static
void	ft_draw_line(t_window *img, t_point p1, t_point p2)
{
	t_line	line;
	int		x;
	int		y;
	int		e2;

	x = (int)roundf(p1.x);
	y = (int)roundf(p1.y);
	ft_init_line(&line, x, y, (int)roundf(p2.x), (int)roundf(p2.y));
	while (1)
	{
		if (line.total_steps > 0)
			line.t = (float)line.current_steps / (float)line.total_steps;
		else
			line.t = 0.0f;
		line.color = ft_interpolate_color(p1.color, p2.color, line.t);
		ft_put_pixel(img, x, y, line.color);
		if (x == line.x1 && y == line.y1)
			break ;
		e2 = 2 * line.err;
		if (e2 >= line.dy)
		{
			line.err += line.dy;
			x += line.inc_x;
		}
		if (e2 <= line.dx)
		{
			line.err += line.dx;
			y += line.inc_y;
		}
		line.current_steps++;
	}
}

/*
** V-01 fix: vertices are visited back-to-front via map->order (sorted by
** ft_sort_order each frame from the depth key computed in ft_iso), instead
** of fixed row-major order. Row-major only matches the painter's order at
** the initial orientation; once the model is rotated, far lines were
** painted over near ones, flattening the perspective.
*/
void	ft_connect(t_window *img, t_map *map)
{
	unsigned int	k;
	unsigned int	idx;
	int				i;
	int				j;

	k = 0;
	while (k < map->size)
	{
		idx = map->order[k];
		i = (int)(idx / (unsigned int)map->cols);
		j = (int)(idx % (unsigned int)map->cols);
		if (j + 1 < map->cols)
			ft_draw_line(img, map->grid[idx], map->grid[idx + 1]);
		if (i + 1 < map->rows)
			ft_draw_line(img, map->grid[idx], \
map->grid[idx + (unsigned int)map->cols]);
		k++;
	}
}
