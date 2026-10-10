/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:06:59 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (SDL2 port: SDL teardown, no exit in loop) */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

#ifdef __EMSCRIPTEN__
# include <emscripten/emscripten.h>
#endif

/*
** Shared teardown used by both exit paths. Every resource is NULL-guarded,
** so the cleanup is safe to run from any startup failure point.
*/
static
void	ft_cleanup(t_env *env)
{
	int	i;

	if (env->map)
	{
		ft_clean_map(env->map);
		env->map = NULL;
	}
	if (env->map_files)
	{
		i = 0;
		while (i < env->map_count)
			free(env->map_files[i++]);
		free(env->map_files);
		env->map_files = NULL;
	}
	ft_platform_quit(env);
}

/*
** SDL2 port: ft_clean_exit (window cross / ESC / SDL_QUIT) no longer
** exit()s mid-frame — it drops the running flag so the native loop in
** main() terminates and main performs the teardown (ft_shutdown). Under
** Emscripten it additionally cancels the main loop; with the simulating
** main loop the wasm runtime keeps the page alive and the browser
** reclaims resources.
*/
int	ft_clean_exit(void *param)
{
	((t_env *)param)->running = 0;
# ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
# endif
	return (0);
}

/*
** L-02 fix: two distinct exit paths. Startup/parse failures (pre-loop)
** report failure via exit(EXIT_FAILURE); the clean path returns from
** main() with success.
*/
int	ft_fail_exit(void *param)
{
	ft_cleanup((t_env *)param);
	exit(EXIT_FAILURE);
	return (0);
}

/*
** Called by main() after the frame loop exits: full teardown.
*/
void	ft_shutdown(t_env *env)
{
	ft_cleanup(env);
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
** P-01 fix: single memset over the frame buffer instead of millions of
** ft_put_pixel calls. SDL2 port: addr is a contiguous w*h Uint32 buffer
** owned by us, so there is no line_length padding to account for.
*/
void	ft_clear_image(t_window *window)
{
	ft_memset(window->addr, 0, \
(size_t)window->w * (size_t)window->h * sizeof(unsigned int));
}
