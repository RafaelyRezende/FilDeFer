/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:22:09 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/05 12:25:56 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
int	ft_color_range_lower(float norm, int *color1, int *color2)
{
	float	t;

	if (norm < 0.2f)
	{
		t = norm / 0.2f;
		*color1 = ft_rgb2int(0, 0, 50);
		*color2 = ft_rgb2int(100, 100, 200);
		return (ft_interpolate_color(*color1, *color2, t));
	}
	else if (norm < 0.4f)
	{
		t = (norm - 0.2f) / 0.2f;
		*color1 = ft_rgb2int(100, 100, 200);
		*color2 = ft_rgb2int(255, 255, 150);
		return (ft_interpolate_color(*color1, *color2, t));
	}
	else
		return (-1);
}

static
int	ft_color_range_upper(float norm, int *color1, int *color2)
{
	float	t;

	if (norm < 0.7f)
	{
		t = (norm - 0.4f) / 0.3f;
		*color1 = ft_rgb2int(255, 255, 150);
		*color2 = ft_rgb2int(50, 200, 50);
		return (ft_interpolate_color(*color1, *color2, t));
	}
	else if (norm < 0.9f)
	{
		t = (norm - 0.7f) / 0.2f;
		*color1 = ft_rgb2int(50, 200, 50);
		*color2 = ft_rgb2int(150, 100, 50);
		return (ft_interpolate_color(*color1, *color2, t));
	}
	else
		return (-1);
}

int	ft_height_to_color(t_env *env, float z)
{
	float	norm;
	int		color1;
	int		color2;
	float	t;

	if (isnan(env->limits.z_max) || isnan(env->limits.z_min) || isnan(z))
		return (ft_rgb2int(255, 0, 0));
	if (env->limits.z_max - env->limits.z_min < 0.000001f)
		return (ft_rgb2int(100, 200, 100));
	norm = (z - env->limits.z_min) / (env->limits.z_max - env->limits.z_min);
	if (norm < 0.4f)
		return (ft_color_range_lower(norm, &color1, &color2));
	else if (norm < 0.9f)
		return (ft_color_range_upper(norm, &color1, &color2));
	else
	{
		t = (norm - 0.9f) / 0.1f;
		color1 = ft_rgb2int(150, 100, 50);
		color2 = ft_rgb2int(255, 255, 255);
		return (ft_interpolate_color(color1, color2, t));
	}
}
