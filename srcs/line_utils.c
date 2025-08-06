/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:45:19 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/06 20:46:00 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

void	ft_init_line(t_line *line, t_point p1, t_point p2)
{
	line->dx = fabs(p2.x - p1.x);
	line->dy = fabs(p2.y - p1.y);
	line->two_dy = 2 * line->dy;
	line->current_steps = 0.0f;
	if (line->dx > line->dy)
		line->param = line->two_dy - line->dx;
	else
		line->param = 2 * line->dx - line->dy;
	if (p2.x > p1.x)
		line->inc_x = 1;
	else
		line->inc_x = -1;
	if (p2.y > p1.y)
		line->inc_y = 1;
	else
		line->inc_y = -1;
	if (line->dx > line->dy)
		line->total_steps = line->dx;
	else
		line->total_steps = line->dy;
	line->color = 0xffffff;
}

void	ft_put_pixel(t_window *window, float width, float heigth, float color)
{
	char	*dst;
	int		val;

	if (width < 0 || heigth < 0 || width > SCREEN_W || heigth > SCREEN_H)
		return ;
	val = (int)heigth * window->line_length + \
(int)width * (window->bits_per_pixel / 8);
	dst = window->addr + val;
	*(unsigned int *)dst = color;
}
