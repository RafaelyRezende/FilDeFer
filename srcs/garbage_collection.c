/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:06:59 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/28 16:15:00 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

void	ft_clean_map(t_map *map)
{
	if (map->grid)
		free(map->grid);
	if (map->indices)
		free(map->indices);
	free(map);
}

void	ft_clear_image(t_window *window)
{
	int	x;
	int	y;
	int	color;

	color = 0X000000;
	y = 0;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			ft_put_pixel(window, x, y, color);
			x++;
		}
		y++;
	}
}
