/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:49:07 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (SDL2/WebAssembly port: unified ft_frame) */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

#ifdef __EMSCRIPTEN__
# include <emscripten/emscripten.h>
# define MAPS_DIR "/maps"
#else
# define MAPS_DIR "maps"
#endif

static
int	ft_error(const char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

static
void	ft_init_env(t_env *this)
{
	ft_memset(this, 0, sizeof(t_env));
	this->needs_redraw = 1;
	this->running = 1;
}

/*
** Default preloaded map list used for startup (argc == 1) and Tab cycling.
** Paths are duplicated so ft_cleanup can free them uniformly.
*/
static
int	ft_setup_maps(t_env *this)
{
	this->map_count = 2;
	this->map_files = (char **)ft_calloc(this->map_count + 1, sizeof(char *));
	if (!this->map_files)
		return (-1);
	this->map_files[0] = ft_strdup(MAPS_DIR "/valid.fdf");
	this->map_files[1] = ft_strdup(MAPS_DIR "/pyramid.fdf");
	if (!this->map_files[0] || !this->map_files[1])
		return (-1);
	this->map_index = 0;
	return (0);
}

/*
** L-03 fix: validate against the LAST dot (ft_strrchr) and require it to
** come after the last path separator, so directories containing dots no
** longer cause false rejections. Prints usage and exits non-zero instead
** of a silent exit(0).
*/
static
void	ft_checker_path(char *path)
{
	char	*dot;
	char	*slash;

	dot = ft_strrchr(path, '.');
	slash = ft_strrchr(path, '/');
	if (!dot || (slash && dot < slash) || ft_strcmp(dot, ".fdf") != 0)
	{
		ft_putstr_fd("Usage: ./fdf <map.fdf>\n", 2);
		exit(EXIT_FAILURE);
	}
}

/*
** One frame iteration, shared by the native loop and the Emscripten main
** loop: pump events, redraw only when the dirty flag is raised
** (P-04 gating), always present.
*/
int	ft_frame(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	ft_platform_events(env);
	if (env->needs_redraw)
	{
		env->needs_redraw = 0;
		ft_rotate_map(env);
	}
	ft_platform_present(env);
	return (0);
}

#ifdef FDF_TEST_HOOK
/*
** Optional headless smoke-test hook (make testhook): render
** FDF_HEADLESS_FRAMES frames (default 1) and leave the loop cleanly.
*/
static
int	ft_hook_frames(void)
{
	const char	*s;
	int			n;

	s = getenv("FDF_HEADLESS_FRAMES");
	if (!s || !*s)
		return (1);
	n = ft_atoi((char *)s);
	if (n <= 0)
		return (1);
	return (n);
}

static
int	ft_run_loop(t_env *env)
{
	int	frames;

	frames = ft_hook_frames();
	while (env->running && frames-- > 0)
		ft_frame(env);
	ft_shutdown(env);
	return (0);
}

#elif defined(__EMSCRIPTEN__)
/*
** Emscripten's main-loop callback is void(void *); ft_frame returns int
** (native loop idiom), so adapt it with a tiny wrapper.
*/
static
void	ft_frame_wasm(void *param)
{
	ft_frame(param);
}

static
int	ft_run_loop(t_env *env)
{
	emscripten_set_main_loop_arg(ft_frame_wasm, env, 0, 1);
	ft_shutdown(env);
	return (0);
}

#else
static
int	ft_run_loop(t_env *env)
{
	while (env->running)
	{
		ft_frame(env);
		SDL_Delay(8);
	}
	ft_shutdown(env);
	return (0);
}
#endif

int	main(int argc, char **argv)
{
	t_env		this;
	const char	*path;

	ft_init_env(&this);
	if (argc > 2)
		return (ft_error("usage: ./fdf [map.fdf]"));
	if (ft_setup_maps(&this) < 0)
		return (ft_fail_exit(&this));
	if (argc == 2)
	{
		ft_checker_path(argv[1]);
		path = argv[1];
	}
	else
		path = this.map_files[0];
	if (ft_platform_init(&this, NAME, DEFAULT_W, DEFAULT_H) < 0)
		return (ft_fail_exit(&this));
	if (ft_load_map_file(&this, path) < 0)
		return (ft_fail_exit(&this));
	ft_ui_init(&this);
	return (ft_run_loop(&this));
}
