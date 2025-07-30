/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:54 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/30 18:10:26 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

//------------------------------CONSTRUCTORS----------------------------------
t_vec3	ft_vec3_constructor(float x, float y, float z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_quat	ft_quat_constructor(float w, float x, float y, float z)
{
	t_quat	q;

	q.w = w;
	q.x = x;
	q.y = y;
	q.z = z;
	return (q);
}

//------------------------------VECTOR MATH-----------------------------------
t_vec3	ft_vec3_norm(t_vec3 u)
{
	float	squared;

	squared = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
	return (ft_vec3_scale(u, 1.0f / squared));
}

t_vec3	ft_vec3_add(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.x = u.z + v.z;
	return (result);
}

float	ft_vec3_mult(t_vec3 u, t_vec3 v)
{
	float	result;

	result = u.x * v.x + u.y * v.y + u.z * v.z;
	return (result);
}

t_vec3	ft_vec3_scale(t_vec3 u, float scaler)
{
	t_vec3	result;

	result.x = u.x * scaler;
	result.y = u.y * scaler;
	result.z = u.z * scaler;
	return (result);
}

//------------------------------QUATERNION------------------------------------

t_quat	ft_conjugate(t_quat q)
{
	return (ft_quat_constructor(q.w, -q.x, -q.y, -q.z));
}

t_quat	ft_quat_mult(t_quat a, t_quat b)
{
	t_quat	result;
	float	w;
	float	x;
	float	y;
	float	z;

	w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	y = a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z;
	z = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x;
	result = ft_quat_constructor(w, x, y ,z);
	return (result);
}

t_quat	ft_quat_from_angle(t_vec3 axis, float angle)
{
	t_quat	result;
	float	half_angle;
	float	sin_half;

	axis = ft_vec3_norm(axis);
	half_angle = angle * 0.5f;
	sin_half = sin(half_angle);
	result = ft_quat_constructor(cos(half_angle),\
	axis.x * sin_half,\
	axis.y * sin_half,\
	axis.z * sin_half);
	return (result);
}

t_vec3	ft_rotate_vector(t_quat q, t_vec3 u)
{
	t_quat	tmp;
	t_quat	baseQuat;
	t_vec3	result;

	baseQuat = ft_quat_constructor(0.0f, u.x, u.y, u.z);
	tmp = ft_quat_mult(ft_quat_mult(q, baseQuat),ft_conjugate(q));
	result = ft_vec3_constructor(tmp.x, tmp.y, tmp.z);
	return (result);
}
/*
void	ft_iso(t_map **map, float scaler)
{
	unsigned int	i;
	float			tmpX;
	float			tmpY;

	i = 0;
	while (i < (*map)->size)
	{
		tmpX = (*map)->grid[i].x_ori;
		tmpY = (*map)->grid[i].y_ori;
		(*map)->grid[i].x = (tmpX - tmpY) * ISO_X;
		(*map)->grid[i].y = (tmpX + tmpY) * ISO_Y - (*map)->grid[i].z_ori;
		(*map)->grid[i].x = (*map)->grid[i].x * scaler + SCREEN_X;
		(*map)->grid[i].y = (*map)->grid[i].y * scaler + SCREEN_Y;
		i++;
	}
}
*/
void	ft_apply_rotation(t_env *env, float scaler)
{
	unsigned int	i;
	t_vec3		orig;
	t_vec3		rotated;

	i = 0;
	while (i < env->map->size)
	{
		orig = ft_vec3_constructor(env->map->grid[i].x_ori,\
		env->map->grid[i].y_ori,\
		env->map->grid[i].z_ori);
		rotated = ft_rotate_vector(*env->q_axis, orig);
		env->map->grid[i].x = (rotated.x - rotated.y) * ISO_X;
		env->map->grid[i].y = (rotated.x + rotated.y) * ISO_Y - rotated.z;
		env->map->grid[i].x = (env->map->grid[i].x + env->trans_x) * scaler + SCREEN_X + env->trans_x;
		env->map->grid[i].y = (env->map->grid[i].y + env->trans_y) * scaler + SCREEN_Y + env->trans_y;
		i++;
	}
}

void	ft_rotate_map(t_env* env, float rad)
{
	t_quat	rotation;
	t_quat	new_rot;
	t_vec3	v;

	v = ft_vec3_constructor(0.0f, 0.0f, 1.0f);
	rotation = ft_quat_from_angle(v, rad);
	new_rot = ft_quat_mult(rotation, *env->q_axis);
	*env->q_axis = new_rot;
	ft_apply_rotation(env, env->map_scaler);
	ft_sort_map(env->map);
	ft_clear_image(&env->window);
	ft_connect(&env->window, env->map);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->window.img, 0, 0);
}
