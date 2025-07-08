/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:02:01 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/08 15:16:15 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_pixel(t_window *window, int width, int heigth, int color)
{
	char	*dst;
	int val;

	val = heigth * window->line_length + width * (window->bits_per_pixel / 8);
	if (val < 0)
		return ;
	dst = window->addr + val;
	*(unsigned int*)dst = color;
}
