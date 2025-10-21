/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ga_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:54 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/06 20:27:05 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

t_vec3	ft_vec3_constructor(float x, float y, float z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	ft_vec3_norm(t_vec3 u)
{
	float	squared;

	squared = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
	return (ft_vec3_scale(u, 1.0f / squared));
}

inline t_vec3	ft_vec3_add(t_vec3 u, t_vec3 v)
{
	return (ft_vec3_constructor((u.x + v.x), (u.y + v.y), (u.z + v.z)));
}

inline t_vec3	ft_vec3_sub(t_vec3 u, t_vec3 v)
{
	return (ft_vec3_constructor((u.x - v.x), (u.y - v.y), (u.z - v.z)));
}

inline t_vec3	ft_vec3_scale(t_vec3 u, float scaler)
{
	return (ft_vec3_constructor((u.x * scaler), \
(u.y * scaler), (u.z * scaler)));
}
