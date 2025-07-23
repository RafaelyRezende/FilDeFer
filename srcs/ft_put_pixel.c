/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:02:01 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/23 12:19:08 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_pixel(t_window *window, float width, float heigth, float color)
{
	char	*dst;
	int	val;

	if (width < 0 || heigth < 0 || width > MAX_WIDTH || heigth > MAX_HEIGHT)
		return ;
	val = (int)heigth * window->line_length + \
		(int)width * (window->bits_per_pixel / 8);
	dst = window->addr + val;
	*(unsigned int*)dst = color;
}
