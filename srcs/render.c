/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:51:22 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/06 20:51:08 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
void	ft_octant_dy(t_line *line, t_point *p1)
{
	if (line->param < 0)
		line->param += line->two_dy;
	else
	{
		p1->y += line->inc_y;
		line->param += line->two_dy - 2 * line->dx;
	}
	p1->x += line->inc_x;
}

static
void	ft_octant_dx(t_line *line, t_point *p1)
{
	if (line->param < 0)
		line->param += 2 * line->dx;
	else
	{
		p1->x += line->inc_x;
		line->param += 2 * line->dx - line->two_dy;
	}
	p1->y += line->inc_y;
}

static
void	ft_line_step(t_line *line, t_point *p1, t_point *p2)
{
	line->t = line->current_steps / line->total_steps;
	line->color = ft_interpolate_color(p1->color, p2->color, line->t);
}

static
void	ft_draw_line(t_window *img, t_point p1, t_point p2)
{
	t_line	line;

	ft_init_line(&line, p1, p2);
	ft_put_pixel(img, p1.x, p1.y, p1.color);
	if (line.dx > line.dy)
	{
		while (fabs(p1.x - p2.x) > 0.5f)
		{
			ft_line_step(&line, &p1, &p2);
			ft_octant_dy(&line, &p1);
			line.current_steps++;
			ft_put_pixel(img, p1.x, p1.y, line.color);
		}
	}
	else
	{
		while (fabs(p1.y - p2.y) > 0.5f)
		{
			ft_line_step(&line, &p1, &p2);
			ft_octant_dx(&line, &p1);
			line.current_steps++;
			ft_put_pixel(img, p1.x, p1.y, line.color);
		}
	}
}

void	ft_connect(t_window *img, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (j + 1 < map->cols)
				ft_draw_line(img, map->grid[i * map->cols + j], \
map->grid[i * map->cols + j + 1]);
			if (i + 1 < map->rows)
				ft_draw_line(img, map->grid[i * map->cols + j], \
map->grid[(i + 1) * map->cols + j]);
			j++;
		}
		i++;
	}
}
