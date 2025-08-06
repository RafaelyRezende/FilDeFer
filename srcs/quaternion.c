/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:54 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/06 19:54:08 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

t_quat	ft_quat_constructor(float w, float x, float y, float z)
{
	t_quat	q;

	q.w = w;
	q.x = x;
	q.y = y;
	q.z = z;
	return (q);
}

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
	result = ft_quat_constructor(w, x, y, z);
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
	result = ft_quat_constructor(cos(half_angle), \
axis.x * sin_half, \
axis.y * sin_half, \
axis.z * sin_half);
	return (result);
}

t_vec3	ft_rotate_vector(t_quat q, t_vec3 u)
{
	t_quat	tmp;
	t_quat	base_quat;
	t_vec3	result;

	base_quat = ft_quat_constructor(0.0f, u.x, u.y, u.z);
	tmp = ft_quat_mult(ft_quat_mult(q, base_quat), ft_conjugate(q));
	result = ft_vec3_constructor(tmp.x, tmp.y, tmp.z);
	return (result);
}
