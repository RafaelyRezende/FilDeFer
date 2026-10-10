/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:54 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (review fixes: L-09, P-02, P-04, A-03)        */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static void	ft_draw_ui(t_env *env);

/*
** P-02 fix: ft_screen_offset is hoisted here — it depends only on
** frame-level state (zoom, limits), so computing it once per frame
** instead of once per point removes ~`size` redundant computations.
*/
void	ft_apply_rotation(t_env *env)
{
	unsigned int	i;
	t_vec3			orig;
	t_vec3			translated;
	t_vec3			rotated;

	ft_screen_offset(env);
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

/*
** L-09 fix: the accumulated orientation quaternion is updated only when a
** non-zero angle delta exists (no identity multiply every frame), and it
** is normalized after each update to prevent numerical drift over long
** sessions.
** V-01 fix: after the transform, vertices are re-sorted back-to-front
** (ft_sort_order) and ft_connect consumes that order. Without it, the
** fixed row-major rasterization order painted far lines over near ones
** as soon as the model was rotated away from its initial orientation.
*/
void	ft_rotate_map(t_env *env)
{
	t_quat	rotation;
	t_vec3	v;

	if (env->angle != 0.0f)
	{
		v = ft_vec3_constructor(0.0f, 0.0f, 1.0f);
		rotation = ft_quat_from_angle(v, env->angle);
		env->q_axis = ft_quat_norm(ft_quat_mult(rotation, env->q_axis));
	}
	ft_apply_rotation(env);
	ft_sort_order(env->map);
	ft_clear_image(&env->window);
	ft_connect(&env->window, env->map);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->window.img, 0, 0);
}

/*
** P-04 fix: dirty-flag gating. The mlx loop hook fires continuously; the
** full transform + clear + rasterize pipeline now runs only when input
** (or startup) has raised needs_redraw. Idle CPU usage drops to ~zero.
*/
int	ft_display_img(void *param)
{
	t_env	*env;

	env = (t_env *) param;
	if (!env->needs_redraw)
		return (0);
	env->needs_redraw = 0;
	ft_rotate_map(env);
	ft_draw_ui(env);
	return (0);
}

static
void	ft_draw_ui(t_env *env)
{
	int	x;
	int	y;

	x = 30;
	y = 30;
	mlx_string_put(env->mlx, env->mlx_win, x, y, 0X00FF00FF, "Fil der Fer");
	mlx_string_put(env->mlx, env->mlx_win, x, y + 10, 0X00FF00FF, "--------------------------------");
	mlx_string_put(env->mlx, env->mlx_win, x, y + 50, 0X00FF00FF, "BUTTONS");
	mlx_string_put(env->mlx, env->mlx_win, x, y + 90, 0X00FF00FF, "A/W/S/D move image");
	mlx_string_put(env->mlx, env->mlx_win, x, y + 130, 0X00FF00FF, "Q/E rotate image");
	mlx_string_put(env->mlx, env->mlx_win, x, y + 170, 0X00FF00FF, "M/N zoom in & zoom out");
	mlx_string_put(env->mlx, env->mlx_win, x, y + 210, 0X00FF00FF, "1/2 change perspective");
	mlx_string_put(env->mlx, env->mlx_win, x, y + 250, 0X00FF00FF, "-/+ change height");
}
