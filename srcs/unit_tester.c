/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:49:07 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:54 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
int	ft_error(const char *msg)
{
	printf("Error %s...", msg);
	return (-1);
}

static
int	ft_expose(t_env *this)
{
	mlx_put_image_to_window(this->mlx, this->mlx_win, this->window.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	this;

	if (argc != 2)
		return (ft_error("number of arguments"));
	this.mlx = mlx_init();
	this.mlx_win = mlx_new_window(this.mlx, SCREEN_W, SCREEN_H, NAME);
	this.window.img = mlx_new_image(this.mlx, SCREEN_W, SCREEN_H);
	this.window.addr = mlx_get_data_addr(this.window.img, \
&this.window.bits_per_pixel, &this.window.line_length, &this.window.endian);
	if (!this.mlx_win || !this.window.addr)
		ft_clean_exit(&this);
	if ((init_map(argv[1], &this.map)) < 0)
		return (ft_clean_exit(&this));
	ft_get_center(&this);
	mlx_loop_hook(this.mlx, ft_display_img, &this);
	mlx_key_hook(this.mlx_win, ft_keypress, &this);
	mlx_hook(this.mlx_win, 2, 1L << 0, ft_keypress, &this);
	mlx_hook(this.mlx_win, 17, 1L << 17, ft_clean_exit, &this);
	mlx_expose_hook(this.mlx_win, ft_expose, &this);
	ft_display_img(&this);
	return (0);
}
