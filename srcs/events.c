/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:38:03 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/06 19:58:41 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
void	ft_button_translate(int key, t_env *this)
{
	if (key == 119)
		this->trans_y -= TRANS_STEP_Y;
	if (key == 115)
		this->trans_y += TRANS_STEP_Y;
	if (key == 97)
		this->trans_x -= TRANS_STEP_X;
	if (key == 100)
		this->trans_x += TRANS_STEP_X;
}

static
void	ft_button_scale(int key, t_env *this)
{
	if (key == 113)
		this->angle += ANGLE_STEP;
	if (key == 101)
		this->angle -= ANGLE_STEP;
	if (key == 109 && this->zoom_scaler < MAX_ZOOM)
		this->zoom_scaler *= ZOOM_STEP_DOWN;
	if (key == 110 && this->zoom_scaler > MIN_ZOOM)
		this->zoom_scaler *= ZOOM_STEP_UP;
}

static
void	ft_button_toggle(int key, t_env *this)
{
	if (key == 61)
		this->z_scaler += HEIGHT_STEP;
	else if (key == 45)
		this->z_scaler -= HEIGHT_STEP;
	else if (key == 50)
		this->is_iso = 0;
	else if (key == 49)
		this->is_iso = 1;
}

int	ft_keypress(int key, t_env *this)
{
	if (key == 65307)
		ft_clean_exit(this);
	if (key == 119 || key == 115 || key == 97 || key == 100)
		ft_button_translate(key, this);
	if (key == 113 || key == 101 || key == 109 || key == 110)
		ft_button_scale(key, this);
	if (key == 61 || key == 45 || key == 50 || key == 49)
		ft_button_toggle(key, this);
	return (0);
}
