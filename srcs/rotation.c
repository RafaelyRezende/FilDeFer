/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:54 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/05 16:28:57 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

void	ft_apply_rotation(t_env *env)
{
	unsigned int	i;
	t_vec3			orig;
	t_vec3			translated;
	t_vec3			rotated;

	i = 0;
	while (i < env->map->size)
	{
		orig = ft_vec3_constructor(\
env->map->grid[i].x_ori, \
env->map->grid[i].y_ori, \
env->map->grid[i].z_ori);
		translated = ft_vec3_sub(orig, env->grid_center);
		rotated = ft_rotate_vector(env->q_axis, translated);
		rotated = ft_vec3_add(rotated, env->grid_center);
		ft_iso(env, rotated, i);
		i++;
	}
	env->angle = 0.0f;
}

void	ft_rotate_map(t_env *env)
{
	t_quat	rotation;
	t_quat	new_rot;
	t_vec3	v;

	v = ft_vec3_constructor(0.0f, 0.0f, 1.0f);
	rotation = ft_quat_from_angle(v, env->angle);
	new_rot = ft_quat_mult(rotation, env->q_axis);
	env->q_axis = new_rot;
	ft_apply_rotation(env);
	ft_sort_map(env->map);
	ft_clear_image(&env->window);
	ft_connect(&env->window, env->map);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->window.img, 0, 0);
}

int	ft_display_img(t_env *env)
{
	ft_rotate_map(env);
	mlx_loop(env->mlx);
	return (0);
}
