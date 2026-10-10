/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:45:19 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (review fixes: L-01, L-10, P-05)             */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

/*
** P-05 fix: integer Bresenham setup (all octants). dx is kept positive and
** dy negative so the classic `err = dx + dy` formulation steps correctly
** in every direction without any float math or epsilon loop conditions.
*/
void	ft_init_line(t_line *line, int x0, int y0, int x1, int y1)
{
	line->dx = abs(x1 - x0);
	line->dy = -abs(y1 - y0);
	line->x1 = x1;
	line->y1 = y1;
	line->err = line->dx + line->dy;
	line->current_steps = 0;
	if (line->dx > -line->dy)
		line->total_steps = line->dx;
	else
		line->total_steps = -line->dy;
	if (x1 > x0)
		line->inc_x = 1;
	else
		line->inc_x = -1;
	if (y1 > y0)
		line->inc_y = 1;
	else
		line->inc_y = -1;
	line->color = 0xffffff;
}

/*
** L-01 fix: bounds test is >= on both axes. Valid pixel coordinates are
** 0..w-1 / 0..h-1 of the runtime framebuffer size (adaptive resolution:
** the old compile-time SCREEN_W/SCREEN_H test is gone).
** L-10 fix: coordinates and color are int; no float->int conversions.
** SDL2 port: addr is a contiguous Uint32 buffer; the alpha byte is OR-ed
** to 0xFF so the packed pixel lands as opaque ARGB8888.
*/
void	ft_put_pixel(t_window *window, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= window->w || y >= window->h)
		return ;
	window->addr[y * window->w + x] = (unsigned int)color | 0xFF000000u;
}
