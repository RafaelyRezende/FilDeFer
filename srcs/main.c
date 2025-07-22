/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:05:58 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/22 15:30:50 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/*
int	main(int argc, char** argv)
{
	t_window		params_window;
	t_env			params_env;
	t_map4			trans_maprix;
	t_trig_lookup	trig_table;
	t_quat_const	q_const;
	t_trans_vals	trans_vals;

	if (argc != 2)
	{
		ft_printf("Wrong number os arguments.");
		return (-1);
	}
}
*/

void	init_rot_vals(t_trans_vals *obj)
{
	obj->sx = 0.0f;
	obj->sy = 0.0f;
	obj->sz = 0.0f;
	obj->tx = 10.0f;
	obj->ty = 10.0f;
	obj->tz = 0.0f;
	obj->rx = 30.0f;
	obj->ry = 30.0f;
	obj->rz = 0.0f;
}

int	main(int argc, char **argv)
{
	t_window	img;
	t_env		this;
	t_map		*map;
	t_trig_lookup	cache;
	t_trans_vals	obj;

	if (argc != 2)
	{
		perror("Error: Invalid number of arguments");
		return (-1);
	}
	this.mlx = mlx_init();
	this.mlx_win = mlx_new_window(this.mlx, 1920, 1080, "WINWINWIN");
	img.img = mlx_new_image(this.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	map = malloc(sizeof(t_map));
	map->mapCol = -1;
	map->mapRow = 0;
	if (init_map(argv[1], map))
		return (mlx_destroy_window(this.mlx, this.mlx_win));
	init_tables(&cache);
	init_rot_vals(&obj);
	ft_pipeline(map, obj, cache);
	ft_connect(&img, map);
	mlx_put_image_to_window(this.mlx, this.mlx_win, img.img, 0, 0);
	mlx_loop(this.mlx);
}
