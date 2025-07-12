/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:05:58 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/12 18:47:15 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_window	img;
	t_env_vars	this;
	t_vec3		*mat;
	int		ne;
	int		i;

	if (argc != 2)
	{
		perror("Error: Invalid number of arguments");
		return (-1);
	}
	this.mlx = mlx_init();
	this.mlx_win = mlx_new_window(this.mlx, 1920, 1080, "WINWINWIN");
	img.img = mlx_new_image(this.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mat = ft_parser(argv[1]);
	ne = mat->nrows * mat->ncols;
	i = 0;
	/*
	while (i < ne)
	{
		ft_printf("x: %d, ", image.mat->x_i[i]);
		ft_printf("y: %d, ", image.mat->y_i[i]);
		ft_printf("z: %d", image.mat->z_i[i]);
		ft_printf("\n");
		i++;
	}
	*/
	ft_connect(&img, mat);
	mlx_put_image_to_window(this.mlx, this.mlx_win, img.img, 0, 0);
	mlx_loop(this.mlx);
}
