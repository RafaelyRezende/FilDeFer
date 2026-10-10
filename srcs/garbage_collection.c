/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:06:59 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (review fixes: L-02, P-01, A-03)             */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

/*
** Shared teardown used by both exit paths. Every resource is NULL-guarded,
** so the cleanup is safe to run from any startup failure point.
*/
static
void	ft_cleanup(t_env *env)
{
	if (env->map)
		ft_clean_map(env->map);
	if (env->window.img)
		mlx_destroy_image(env->mlx, env->window.img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
}

/*
** L-02 fix: two distinct exit paths. ft_clean_exit (window cross / ESC)
** reports success; ft_fail_exit (startup/parse failures) reports failure.
** Previously every path, including "map file could not be parsed", ended
** in exit(0), making failures indistinguishable from success in scripts.
*/
int	ft_clean_exit(void *param)
{
	ft_cleanup((t_env *)param);
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_fail_exit(void *param)
{
	ft_cleanup((t_env *)param);
	exit(EXIT_FAILURE);
	return (0);
}

/* V-01 fix: map->order (draw-order permutation) is freed alongside grid. */
void	ft_clean_map(t_map *map)
{
	if (map->order)
		free(map->order);
	if (map->grid)
		free(map->grid);
	free(map);
}

/*
** P-01 fix: single memset over the frame buffer instead of ~2.07M
** ft_put_pixel calls (1920 x 1080, each with bounds checks and float
** conversions). line_length already accounts for per-row padding.
*/
void	ft_clear_image(t_window *window)
{
	ft_memset(window->addr, 0, \
(size_t)SCREEN_H * (size_t)window->line_length);
}
