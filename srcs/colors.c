/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:22:09 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/05 11:20:25 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

int	ft_rgb2int(int red, int green, int blue)
{
	int	res;

	res = (red << 16) | (green << 8) | blue;
	return (res);
}

t_rgb	ft_int2rgb(int color)
{
	t_rgb	res;

	res.r = (color >> 16) & 0XFF;
	res.g = (color >> 8) & 0XFF;
	res.b = color & 0XFF;
	return (res);
}

int	ft_interpolate_color(int color1, int color2, float t)
{
	t_rgb	res;
	t_rgb	c1;
	t_rgb	c2;

	c1 = ft_int2rgb(color1);
	c2 = ft_int2rgb(color2);
	res.r = c1.r + (int)((c2.r - c1.r) * t);
	res.g = c1.g + (int)((c2.g - c1.g) * t);
	res.b = c1.b + (int)((c2.b - c1.b) * t);
	return (ft_rgb2int(res.r, res.g, res.b));
}

void	ft_set_color(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->map->size)
	{
		env->map->grid[i].color = ft_height_to_color(env, \
env->map->grid[i].z_ori);
		i++;
	}
}
