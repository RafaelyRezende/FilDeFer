/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:54 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/01 22:12:53 by rluis-ya         ###   ########.fr       */
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
	return (ft_vec3_constructor((u.x + v.x), (u.y + v.y), (u.z + v.z)));
}

t_vec3	ft_vec3_sub(t_vec3 u, t_vec3 v)
{
	return (ft_vec3_constructor((u.x - v.x), (u.y - v.y), (u.z - v.z)));
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

static
int	ft_init_limits(t_limits *lims)
{
	lims = (t_limits *)ft_calloc(1, sizeof(t_limits));
	if (!lims)
		return (-1);
	lims->x_min = SCREEN_W;
	lims->x_max = -SCREEN_W;
	lims->y_min = SCREEN_H;
	lims->y_max = -SCREEN_H;
	lims->z_min = SCREEN_W;
	lims->z_max = -SCREEN_W;
	return (0);
}

void	ft_set_limits(t_env *env)
{
	unsigned int	i;

	if (ft_init_limits(env->limits) < 0)
		ft_clean_exit(env);
	i = 0;

	while (i < env->map->size)
	{
		if (env->limits->x_min > env->map->grid[i].x_ori)
			env->limits->x_min = env->map->grid[i].x_ori;
		if (env->limits->x_max < env->map->grid[i].x_ori)
			env->limits->x_max = env->map->grid[i].x_ori;
		if (env->limits->y_min > env->map->grid[i].y_ori)
			env->limits->y_min = env->map->grid[i].y_ori;
		if (env->limits->y_max < env->map->grid[i].y_ori)
			env->limits->y_max = env->map->grid[i].y_ori;
		if (env->limits->z_min > env->map->grid[i].z_ori)
			env->limits->z_min = env->map->grid[i].z_ori;
		if (env->limits->z_max < env->map->grid[i].z_ori)
			env->limits->z_max = env->map->grid[i].z_ori;
		i++;
	}
}

void	ft_get_center(t_env *env)
{
	env->trans_x = 0.0f;
	env->trans_y = 0.0f;
	env->q_axis = (t_quat *)ft_calloc(1, sizeof(t_quat));
	if (!env->q_axis)
		ft_clean_exit(env);
	*(env->q_axis) = ft_quat_constructor(1.0f, 0.0f, 0.0f, 0.0f);
	ft_set_limits(env);
	env->max_dim = fmaxf(env->limits->x_max - env->limits->x_min, env->limits->y_max - env->limits->y_min);
	env->map_scaler = (SCREEN_W * 0.7f) / (env->max_dim * 2.0f);
	env->grid_center = ft_vec3_constructor(\
			(env->limits->x_max + env->limits->x_min) * 0.5f,\
			(env->limits->y_max + env->limits->y_min) * 0.5f,\
			(env->limits->z_max + env->limits->z_min)* 0.5f);
}

void	ft_iso(t_env *env, t_vec3 rotated, unsigned int i)
{
	float		iso_x;
	float		iso_y;

	iso_x = (rotated.x - rotated.y) * ISO_X;
	iso_y = (rotated.x + rotated.y) * ISO_Y - rotated.z;
	env->map->grid[i].x = (iso_x + env->trans_x) * env->map_scaler + SCREEN_X - (env->max_dim * ISO_X * env->map_scaler);
	env->map->grid[i].y = (iso_y + env->trans_y) * env->map_scaler + SCREEN_Y - (env->max_dim * ISO_Y * env->map_scaler);
	i++;
}

void	ft_apply_rotation(t_env *env)
{
	unsigned int	i;
	t_vec3		orig;
	t_vec3		translated;
	t_vec3		rotated;

	i = 0;
	while (i < env->map->size)
	{
		orig = ft_vec3_constructor(\
		(env->map->grid[i].x_ori),\
		(env->map->grid[i].y_ori),\
		(env->map->grid[i].z_ori));
		translated = ft_vec3_sub(orig, env->grid_center);
		rotated = ft_rotate_vector(*env->q_axis, translated);
		rotated = ft_vec3_add(rotated, env->grid_center);
		ft_iso(env, rotated, i);
		i++;
	}
}

void	ft_rotate_map(t_env* env, t_vec3 v, float rad)
{
	t_quat	rotation;
	t_quat	new_rot;

	rotation = ft_quat_from_angle(v, rad);
	new_rot = ft_quat_mult(rotation, *env->q_axis);
	*env->q_axis = new_rot;
	ft_apply_rotation(env);
	ft_sort_map(env->map);
	ft_clear_image(&env->window);
	ft_connect(&env->window, env->map);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->window.img, 0, 0);
}
