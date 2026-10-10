/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jps (SDL2/WebAssembly port)                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   SDL2 window/renderer/texture/framebuffer lifecycle, event pump,         */
/*   resize handling, map cycling and present(). Replaces minilibx.          */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
int	ft_sdl_error(const char *what)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)what, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)SDL_GetError(), 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

static
int	ft_create_texture(t_env *env, int w, int h)
{
	env->window.texture = SDL_CreateTexture(env->window.renderer, \
SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
	if (!env->window.texture)
		return (ft_sdl_error("SDL_CreateTexture"));
	SDL_SetTextureBlendMode(env->window.texture, SDL_BLENDMODE_NONE);
	return (0);
}

int	ft_platform_init(t_env *env, const char *title, int w, int h)
{
	Uint32	flags;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return (ft_sdl_error("SDL_Init"));
	flags = SDL_WINDOW_RESIZABLE;
# ifndef __EMSCRIPTEN__
	flags |= SDL_WINDOW_MAXIMIZED;
# endif
	env->window.win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, \
SDL_WINDOWPOS_CENTERED, w, h, flags);
	if (!env->window.win)
		return (ft_sdl_error("SDL_CreateWindow"));
	env->window.renderer = SDL_CreateRenderer(env->window.win, -1, \
SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!env->window.renderer)
		env->window.renderer = SDL_CreateRenderer(env->window.win, -1, \
SDL_RENDERER_SOFTWARE);
	if (!env->window.renderer)
		return (ft_sdl_error("SDL_CreateRenderer"));
	SDL_GetWindowSize(env->window.win, &env->window.w, &env->window.h);
	env->window.addr = (unsigned int *)malloc(sizeof(unsigned int) * \
(size_t)env->window.w * (size_t)env->window.h);
	if (!env->window.addr)
		return (ft_sdl_error("framebuffer malloc"));
	return (ft_create_texture(env, env->window.w, env->window.h));
}

/*
** Adaptive resolution: reallocate the CPU framebuffer and recreate the
** streaming texture at the new size; force a full redraw next frame.
*/
void	ft_platform_resize(t_env *env, int w, int h)
{
	unsigned int	*addr;

	if (w <= 0 || h <= 0)
		return ;
	if (w == env->window.w && h == env->window.h)
		return ;
	addr = (unsigned int *)malloc(sizeof(unsigned int) * \
(size_t)w * (size_t)h);
	if (!addr)
		return ;
	free(env->window.addr);
	env->window.addr = addr;
	env->window.w = w;
	env->window.h = h;
	if (env->window.texture)
		SDL_DestroyTexture(env->window.texture);
	env->window.texture = NULL;
	if (ft_create_texture(env, w, h) < 0)
	{
		ft_clean_exit(env);
		return ;
	}
	env->needs_redraw = 1;
}

void	ft_platform_events(t_env *env)
{
	SDL_Event	ev;

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
			ft_clean_exit(env);
		else if (ev.type == SDL_WINDOWEVENT && \
ev.window.event == SDL_WINDOWEVENT_RESIZED)
			ft_platform_resize(env, ev.window.data1, ev.window.data2);
		else if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_TAB)
				ft_cycle_map(env);
			else
				ft_keypress(ev.key.keysym.sym, env);
		}
		else if (ev.type == SDL_DROPFILE)
		{
			if (ft_load_map_file(env, ev.drop.file) < 0)
				ft_putstr_fd("Error: could not load dropped map\n", 2);
			SDL_free(ev.drop.file);
		}
	}
}

/*
** Upload the CPU framebuffer, blit it, overlay the cached controls texture
** (if the font loaded) at 30,30, and swap.
*/
void	ft_platform_present(t_env *env)
{
	SDL_Rect	dst;

	if (!env->window.renderer || !env->window.texture || !env->window.addr)
		return ;
	SDL_UpdateTexture(env->window.texture, NULL, env->window.addr, \
env->window.w * (int)sizeof(unsigned int));
	SDL_RenderClear(env->window.renderer);
	SDL_RenderCopy(env->window.renderer, env->window.texture, NULL, NULL);
	if (env->ui_tex)
	{
		dst.x = 30;
		dst.y = 30;
		dst.w = env->ui_tex_w;
		dst.h = env->ui_tex_h;
		SDL_RenderCopy(env->window.renderer, env->ui_tex, NULL, &dst);
	}
	SDL_RenderPresent(env->window.renderer);
}

void	ft_platform_quit(t_env *env)
{
	ft_ui_destroy(env);
	if (env->window.texture)
		SDL_DestroyTexture(env->window.texture);
	env->window.texture = NULL;
	if (env->window.renderer)
		SDL_DestroyRenderer(env->window.renderer);
	env->window.renderer = NULL;
	if (env->window.win)
		SDL_DestroyWindow(env->window.win);
	env->window.win = NULL;
	if (env->window.addr)
		free(env->window.addr);
	env->window.addr = NULL;
	SDL_Quit();
}

/*
** Load a map from an arbitrary path (drag-and-drop, Tab cycling, startup).
** The new map is fully parsed BEFORE the old one is dropped, so a parse
** failure keeps the current map on screen. ft_get_center resets the
** rotation quaternion, translations, zoom and projection to defaults.
*/
int	ft_load_map_file(t_env *env, const char *path)
{
	t_map	*new_map;

	new_map = NULL;
	if (init_map(path, &new_map) < 0 || !new_map)
	{
		ft_putstr_fd("Error: failed to parse map: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (env->map)
		ft_clean_map(env->map);
	env->map = new_map;
	ft_get_center(env);
	env->needs_redraw = 1;
	return (0);
}

void	ft_cycle_map(t_env *env)
{
	int	next;

	if (!env->map_files || env->map_count <= 0)
		return ;
	next = (env->map_index + 1) % env->map_count;
	if (ft_load_map_file(env, env->map_files[next]) == 0)
		env->map_index = next;
}
