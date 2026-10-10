/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:54 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (review fixes: L-06, L-10, P-02, V-01)     */
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

/*
** L-06 fix: max_dim is clamped to a small positive floor before it is used
** as a divisor. A single-point map (or any map with zero x/y span) used to
** produce base_scaler = inf and NaN coordinates downstream.
*/
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
	if (env->max_dim < MIN_DIM_EPSILON)
		env->max_dim = 1.0f;
	env->base_scaler = (SCREEN_W * 0.7f) / (env->max_dim * 2.0f);
}

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
	env->z_scaler = 0.6f;
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

/*
** P-02 fix: ft_screen_offset is no longer called here; it runs once per
** frame at the top of ft_apply_rotation.
** L-10 fix: the trailing `i++` on a by-value parameter was a no-op and has
** been removed.
** V-01 fix: also compute the painter's-algorithm depth key. The
** projection collapses every point along its kernel direction v; for the
** isometric map sx=(x-y)*ISO_X, sy=(x+y)*ISO_Y-z*z_scaler the kernel is
** v=(z_scaler, z_scaler, 1), so depth = z_scaler*(x+y) + z. The top-down
** (parallel) map sx=x-y, sy=x+y has kernel (0,0,1), so depth = z.
** Drawing in ascending depth order is back-to-front for a viewer on the
** +v side. This form is exact and continuous in z_scaler: at z_scaler=0
** it degenerates to depth=z with no division and no singularity.
*/
void	ft_iso(t_env *env, t_vec3 rotated, unsigned int i)
{
	float	iso_x;
	float	iso_y;

	if (!env->is_iso)
	{
		iso_x = rotated.x - rotated.y;
		iso_y = rotated.x + rotated.y;
		env->map->grid[i].depth = rotated.z;
	}
	else
	{
		iso_x = (rotated.x - rotated.y) * ISO_X;
		iso_y = (rotated.x + rotated.y) * ISO_Y - (rotated.z * env->z_scaler);
		env->map->grid[i].depth = env->z_scaler * (rotated.x + rotated.y) \
+ rotated.z;
	}
	env->map->grid[i].x = (iso_x + env->trans_x) * \
env->map_scaler + env->offset_x;
	env->map->grid[i].y = (iso_y + env->trans_y) * \
env->map_scaler + env->offset_y;
}
