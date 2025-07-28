/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:38:03 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/28 16:25:45 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

int	ft_keypress(int key, t_env *this)
{
    printf("Keycode: %d\n", key);
	fflush(stdout);
	if (key == 65307)
	{
		if (this->q_axis)
			return (-1);
		ft_clean_map(this->map);
		mlx_destroy_image(this->mlx, this->window.img);
		mlx_destroy_window(this->mlx, this->mlx_win);
		mlx_destroy_display(this->mlx);
		free(this->mlx);
		exit (0);
	}
	else if (key == 97)
		ft_rotate_map(this, ANGLE_STEP);
	else if (key == 100)
		ft_rotate_map(this, -ANGLE_STEP);
	return (0);
}
