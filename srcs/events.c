/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:38:03 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/28 09:30:05 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

int	ft_keypress(int key, t_env *this)
{
    printf("Keycode: %d\n", key);
	fflush(stdout);
	if (key == 65307)
	{
		mlx_destroy_image(this->mlx, this->window.img);
		mlx_destroy_window(this->mlx, this->mlx_win);
		mlx_destroy_display(this->mlx);
		free(this->mlx);
		exit (0);
	}
	return (0);
}
