/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jps (SDL2/WebAssembly port)                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   SDL2_ttf controls overlay. The 8 static help lines are rendered ONCE  */
/*   into a cached texture (ui_tex). Every failure here is non-fatal: a    */
/*   warning is logged and the program simply runs without the overlay.    */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

#ifdef __EMSCRIPTEN__
# define FONT_PATH "/assets/DejaVuSans.ttf"
#else
# define FONT_PATH "assets/DejaVuSans.ttf"
#endif

static const char	*g_ui_lines[8] = {
	"Fil der Fer",
	"--------------------------------",
	"BUTTONS",
	"A/W/S/D move image",
	"Q/E rotate image",
	"M/N zoom in & zoom out",
	"1/2 change perspective",
	"-/+ change height"
};

static
void	ft_ui_warn(const char *what)
{
	ft_putstr_fd("Warning: ", 2);
	ft_putstr_fd((char *)what, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)TTF_GetError(), 2);
	ft_putstr_fd("\n", 2);
}

static
void	ft_free_lines(SDL_Surface **lines, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (lines[i])
			SDL_FreeSurface(lines[i]);
		i++;
	}
}

/*
** Render each help line (magenta, blended) and measure the widest one.
*/
static
int	ft_render_lines(t_env *env, SDL_Surface **lines, int *out_w)
{
	SDL_Color	color;
	int			i;

	color.r = 255;
	color.g = 0;
	color.b = 255;
	color.a = 255;
	*out_w = 0;
	i = 0;
	while (i < 8)
	{
		lines[i] = TTF_RenderUTF8_Blended(env->font, g_ui_lines[i], color);
		if (!lines[i])
		{
			ft_free_lines(lines, i);
			return (-1);
		}
		if (lines[i]->w > *out_w)
			*out_w = lines[i]->w;
		i++;
	}
	return (0);
}

/*
** Blit the 8 rendered lines onto one transparent RGBA canvas surface and
** cache the result as env->ui_tex (alpha-blended so the framebuffer shows
** through between glyphs).
*/
static
void	ft_ui_build(t_env *env)
{
	SDL_Surface	*lines[8];
	SDL_Surface	*canvas;
	SDL_Rect	dst;
	int			i;
	int			w;

	i = -1;
	while (++i < 8)
		lines[i] = NULL;
	if (ft_render_lines(env, lines, &w) < 0)
		return ;
	env->ui_tex_h = TTF_FontLineSkip(env->font) * 8;
	env->ui_tex_w = w;
	canvas = SDL_CreateRGBSurfaceWithFormat(0, w, env->ui_tex_h, 32, \
SDL_PIXELFORMAT_ARGB8888);
	if (!canvas)
		return (ft_free_lines(lines, 8));
	i = -1;
	while (++i < 8)
	{
		dst.x = 0;
		dst.y = i * TTF_FontLineSkip(env->font);
		dst.w = lines[i]->w;
		dst.h = lines[i]->h;
		SDL_BlitSurface(lines[i], NULL, canvas, &dst);
	}
	ft_free_lines(lines, 8);
	env->ui_tex = SDL_CreateTextureFromSurface(env->window.renderer, canvas);
	SDL_FreeSurface(canvas);
	if (env->ui_tex)
		SDL_SetTextureBlendMode(env->ui_tex, SDL_BLENDMODE_BLEND);
}

void	ft_ui_init(t_env *env)
{
	if (TTF_Init() < 0)
	{
		ft_ui_warn("TTF_Init");
		return ;
	}
	env->font = TTF_OpenFont(FONT_PATH, 16);
	if (!env->font)
	{
		ft_ui_warn("TTF_OpenFont " FONT_PATH);
		TTF_Quit();
		return ;
	}
	ft_ui_build(env);
	if (!env->ui_tex)
		ft_ui_warn("overlay texture");
}

void	ft_ui_destroy(t_env *env)
{
	if (env->ui_tex)
		SDL_DestroyTexture(env->ui_tex);
	env->ui_tex = NULL;
	if (env->font)
		TTF_CloseFont(env->font);
	env->font = NULL;
	TTF_Quit();
}
