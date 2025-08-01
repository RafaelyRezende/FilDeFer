/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:38:03 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/01 19:35:43 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

int	ft_keypress(int key, t_env *this)
{
//	t_vec3	axis_x;
//	t_vec3	axis_y;
	t_vec3	axis_z;

//	axis_x = ft_vec3_constructor(1.0f, 0.0f, 0.0f);
//	axis_y = ft_vec3_constructor(0.0f, 1.0f, 0.0f);
	axis_z = ft_vec3_constructor(0.0f, 0.0f, 1.0f);
    printf("Keycode: %d\n", key);
	fflush(stdout);
	if (key == 65307)
	{
		free(this->q_axis);
		ft_clean_map(this->map);
		mlx_destroy_image(this->mlx, this->window.img);
		mlx_destroy_window(this->mlx, this->mlx_win);
		mlx_destroy_display(this->mlx);
		free(this->mlx);
		exit (0);
	}
	else if (key == 119)
	{
		this->trans_y -= TRANS_STEP_Y;
		ft_rotate_map(this, axis_z, 0.0f);
	}
	else if (key == 115)
	{
		this->trans_y += TRANS_STEP_Y;
		ft_rotate_map(this, axis_z, 0.0f);
	}
	else if (key == 97)
	{
		this->trans_x -= TRANS_STEP_X;
		ft_rotate_map(this, axis_z, 0.0f);
	}
	else if (key == 100)
	{
		this->trans_x += TRANS_STEP_X;
		ft_rotate_map(this, axis_z, 0.0f);
	}
	else if (key == 113)
		ft_rotate_map(this, axis_z, ANGLE_STEP);
	else if (key == 101)
		ft_rotate_map(this, axis_z, -ANGLE_STEP);
	return (0);
}
