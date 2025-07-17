/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:51:22 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/15 14:56:40 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static
void	ft_draw_line(t_window *img, t_point p1, t_point p2, t_line l1)
{
	int	p0;
	int	inc_x;
	int	inc_y;

	if (p1.x > p2.x)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
	}
	p0 = l1.param;
	inc_y = 1;
	if (p1.y > p2.y)
		inc_y = -1;
	inc_x = 1;
	if (p1.x > p2.x)
		inc_x = -1;
	ft_put_pixel(img, p1.x, p1.y, COLOR1);
	while (p1.x < p2.x)
	{
		if (p0 < 0)
			p0 += l1.two_dy;
		else
		{
			p1.y += inc_y;
			p0 += l1.two_dy - 2 * l1.dx;
		}
		p1.x += inc_x;
		ft_put_pixel(img, p1.x, p1.y, COLOR1);
	}
}

static
void	ft_draw_line_too(t_window *img, t_point p1, t_point p2, t_line l1)
{
	int	p0;
	int	inc_x;
	int	inc_y;

	if (p1.y > p2.y)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
	}
	p0 = 2 * l1.dx - l1.dy;
	inc_y = 1;
	if (p1.y > p2.y)
		inc_y = -1;
	inc_x = 1;
	if (p1.x > p2.x)
		inc_x = -1;
	ft_put_pixel(img, p1.x, p1.y, COLOR1);
	while (p1.y < p2.y)
	{
		if (p0 < 0)
			p0 += 2 * l1.dx;
		else
		{
			p1.x += inc_x;
			p0 += 2 * l1.dx - l1.two_dy;
		}
		p1.y += inc_y;
		ft_put_pixel(img, p1.x, p1.y, COLOR1);
	}
}

static
void	ft_draw_edge(t_window *img, t_point p1, t_point p2)
{
	t_line	l1;

	ft_init_line(&l1, p1, p2);
	if (l1.dy > l1.dx)
		ft_draw_line_too(img, p1, p2, l1);
	else
		ft_draw_line(img, p1, p2, l1);
}

static
t_point	ft_transform(int x, int y, int z, int scaler)
{
	double	angle;
	t_point	newPoint;
	int		zMultiplier;
	int		shift;

	angle = PI / 6;
	shift = 200;
	zMultiplier = scaler / 4;
	if (zMultiplier < 1)
		zMultiplier = 1;
	newPoint.x = (int)roundf((x - y) * cos(angle) * scaler);
	newPoint.y = (int)roundf((x + y) * sin(angle) * scaler - z * zMultiplier);
	newPoint.x += WIDTH / 2;
	newPoint.y += HEIGHT / 4;
	return (newPoint);
}

void	ft_connect(t_window *img, t_vec3 *matrix)
{
	int	k;
	int	max;
	int	scaler;
	t_point	p1;
	t_point	p2;

	k = 0;
	scaler = 20;
	max = matrix->nrows * matrix->ncols;
	while(k < max)
	{
		p1 = ft_transform(matrix->x_i[k], matrix->y_i[k], matrix->z_i[k], scaler);
		if (k + 1 < max && ((k + 1) % matrix->ncols))
		{
			p2 = ft_transform(matrix->x_i[k + 1], matrix->y_i[k + 1], matrix->z_i[k + 1], scaler); 
			ft_draw_edge(img, p1, p2);
		}
		if (k + matrix->ncols < max)
		{
			p2 = ft_transform(matrix->x_i[k + matrix->ncols], matrix->y_i[k + matrix->ncols], matrix->z_i[k + matrix->ncols], scaler);
			ft_draw_edge(img, p1, p2);
		}
		k++;
	}
}
