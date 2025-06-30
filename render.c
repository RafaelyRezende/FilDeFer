/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:51:22 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/06/30 17:19:22 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <stdlib.h>

typedef	struct s_env_vars
{
	void	*mlx;
	void	*mlx_win;
}	t_env_vars;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_data;

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	t_env_vars	this;
	t_data		img;

	this.mlx = mlx_init();
	this.mlx_win = mlx_new_window(this.mlx, 100, 50, "WINWINWIN");
	img.img = mlx_new_image(this.mlx, 100, 50);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	ft_put_pixel(&img, 5, 5, 0x00FF0000);
	ft_put_pixel(&img, 5, 10, 0x00FF0000);
	ft_put_pixel(&img, 5, 15, 0x00FF0000);
	ft_put_pixel(&img, 15, 15, 0x00FF0000);
	ft_put_pixel(&img, 15, 10, 0x00FF0000);
	ft_put_pixel(&img, 15, 5, 0x00FF0000);
	ft_put_pixel(&img, 10, 15, 0x00FF0000);
	ft_put_pixel(&img, 10, 10, 0x00FF0000);
	ft_put_pixel(&img, 10, 5, 0x00FF0000);
	mlx_put_image_to_window(this.mlx, this.mlx_win, img.img, 0, 0);
	mlx_loop(this.mlx);
}
