/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:54 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/05 16:36:53 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
t_limits	ft_init_limits(void)
{
	t_limits	limits;

	limits.x_min = SCREEN_W;
	limits.x_max = -SCREEN_W;
	limits.y_min = SCREEN_H;
	limits.y_max = -SCREEN_H;
	limits.z_min = SCREEN_W;
	limits.z_max = -SCREEN_W;
	return (limits);
}

void	ft_set_limits(t_env *env)
{
	unsigned int	i;

	env->limits = ft_init_limits();
	i = 0;
	while (i < env->map->size)
	{
		if (env->limits.x_min > env->map->grid[i].x_ori)
			env->limits.x_min = env->map->grid[i].x_ori;
		if (env->limits.x_max < env->map->grid[i].x_ori)
			env->limits.x_max = env->map->grid[i].x_ori;
		if (env->limits.y_min > env->map->grid[i].y_ori)
			env->limits.y_min = env->map->grid[i].y_ori;
		if (env->limits.y_max < env->map->grid[i].y_ori)
			env->limits.y_max = env->map->grid[i].y_ori;
		if (env->limits.z_min > env->map->grid[i].z_ori)
			env->limits.z_min = env->map->grid[i].z_ori;
		if (env->limits.z_max < env->map->grid[i].z_ori)
			env->limits.z_max = env->map->grid[i].z_ori;
		i++;
	}
	env->max_dim = fmaxf(env->limits.x_max - env->limits.x_min, \
env->limits.y_max - env->limits.y_min);
	env->base_scaler = (SCREEN_W * 0.7f) / (env->max_dim * 2.0f);
}

static
void	ft_screen_offset(t_env *env)
{
	env->map_scaler = env->base_scaler * env->zoom_scaler;
	env->offset_x = SCREEN_X - (env->max_dim * ISO_X * env->map_scaler);
	env->offset_y = SCREEN_Y - (env->max_dim * ISO_Y * env->map_scaler);
}

void	ft_get_center(t_env *env)
{
	env->trans_x = 0.0f;
	env->trans_y = 0.0f;
	env->offset_x = 0.0f;
	env->offset_y = 0.0f;
	env->angle = 0.0f;
	env->zoom_scaler = 1.0f;
	env->z_scaler = 1.0f;
	env->base_scaler = 1.0f;
	env->is_iso = 1;
	env->q_axis = ft_quat_constructor(1.0f, 0.0f, 0.0f, 0.0f);
	ft_set_limits(env);
	ft_set_color(env);
	ft_screen_offset(env);
	env->grid_center = ft_vec3_constructor(\
(env->limits.x_max + env->limits.x_min) * 0.5f, \
(env->limits.y_max + env->limits.y_min) * 0.5f, \
(env->limits.z_max + env->limits.z_min) * 0.5f);
}

void	ft_iso(t_env *env, t_vec3 rotated, unsigned int i)
{
	float	iso_x;
	float	iso_y;

	ft_screen_offset(env);
	if (!env->is_iso)
	{
		iso_x = rotated.x - rotated.y;
		iso_y = rotated.x + rotated.y;
	}
	else
	{
		iso_x = (rotated.x - rotated.y) * ISO_X;
		iso_y = (rotated.x + rotated.y) * ISO_Y - (rotated.z * env->z_scaler);
	}
	env->map->grid[i].x = (iso_x + env->trans_x) * \
env->map_scaler + env->offset_x;
	env->map->grid[i].y = (iso_y + env->trans_y) * \
env->map_scaler + env->offset_y;
	i++;
}
