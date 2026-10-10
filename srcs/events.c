/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:38:03 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (SDL2 port: SDL_Keycode instead of X11)    */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
void	ft_button_translate(SDL_Keycode key, t_env *this)
{
	if (key == SDLK_w)
		this->trans_y -= TRANS_STEP_Y;
	if (key == SDLK_s)
		this->trans_y += TRANS_STEP_Y;
	if (key == SDLK_a)
		this->trans_x -= TRANS_STEP_X;
	if (key == SDLK_d)
		this->trans_x += TRANS_STEP_X;
}

/*
** L-08 fix: zoom is clamped AFTER the multiplicative step, so the value
** can never overshoot MAX_ZOOM / MIN_ZOOM (previously 4.9 * 1.1 = 5.39
** slipped past the gate).
*/
static
void	ft_button_scale(SDL_Keycode key, t_env *this)
{
	if (key == SDLK_q)
		this->angle += ANGLE_STEP;
	if (key == SDLK_e)
		this->angle -= ANGLE_STEP;
	if (key == SDLK_m)
		this->zoom_scaler = fminf(this->zoom_scaler * ZOOM_IN_FACTOR, MAX_ZOOM);
	if (key == SDLK_n)
		this->zoom_scaler = fmaxf(this->zoom_scaler * ZOOM_OUT_FACTOR, MIN_ZOOM);
}

static
void	ft_button_toggle(SDL_Keycode key, t_env *this)
{
	if (key == SDLK_EQUALS)
		this->z_scaler += HEIGHT_STEP;
	else if (key == SDLK_MINUS)
		this->z_scaler -= HEIGHT_STEP;
	else if (key == SDLK_2)
		this->is_iso = 0;
	else if (key == SDLK_1)
		this->is_iso = 1;
}

/*
** SDL2 port: SDL_Keycode replaces the old X11 keysyms; control parity is
** unchanged (WASD translate, Q/E rotate, M/N clamped zoom, 1/2 projection,
** -/= height, ESC quit). Tab (map cycling) and SDL_DROPFILE are handled in
** ft_platform_events (srcs/platform.c).
** P-04 fix: any state-mutating key raises needs_redraw so the frame loop
** redraws exactly once per change instead of every tick.
*/
int	ft_keypress(SDL_Keycode key, void *param)
{
	t_env	*this;

	this = param;
	if (key == SDLK_ESCAPE)
		ft_clean_exit(this);
	if (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d)
		ft_button_translate(key, this);
	else if (key == SDLK_q || key == SDLK_e || key == SDLK_m || key == SDLK_n)
		ft_button_scale(key, this);
	else if (key == SDLK_EQUALS || key == SDLK_MINUS || \
key == SDLK_2 || key == SDLK_1)
		ft_button_toggle(key, this);
	else
		return (0);
	this->needs_redraw = 1;
	return (0);
}
