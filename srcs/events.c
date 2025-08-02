/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:38:03 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/02 19:35:05 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

int	ft_keypress(int key, t_env *this)
{
    printf("Keycode: %d\n", key);
	fflush(stdout);
	if (key == 65307)
	{
		ft_clean_map(this->map);
		mlx_destroy_image(this->mlx, this->window.img);
		mlx_destroy_window(this->mlx, this->mlx_win);
		mlx_destroy_display(this->mlx);
		free(this->mlx);
		exit (0);
	}
	else if (key == 119)
		this->trans_y -= TRANS_STEP_Y;
	else if (key == 115)
		this->trans_y += TRANS_STEP_Y;
	else if (key == 97)
		this->trans_x -= TRANS_STEP_X;
	else if (key == 100)
		this->trans_x += TRANS_STEP_X;
	else if (key == 113)
		this->angle += ANGLE_STEP;
	else if (key == 101)
		this->angle -= ANGLE_STEP;
	else if (key == 109 && this->zoom_scaler < MAX_ZOOM)
		this->zoom_scaler += ZOOM_STEP;
	else if (key == 110 && this->zoom_scaler > MIN_ZOOM)
		this->zoom_scaler -= ZOOM_STEP;
	return (0);
}
