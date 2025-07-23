/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:05:58 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/23 18:10:36 by rluis-ya         ###   ########.fr       */
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

static
void	init_vals(t_trans_vals *obj)
{
	obj->sx = 40.0f;
	obj->sy = 40.0f;
	obj->sz = 40.0f;
	obj->tx = 300.0f;
	obj->ty = 300.0f;
	obj->tz = 0.0f;
	obj->rx = 0.0;
	obj->ry = 0.0;
	obj->rz = 0.0f;
}

int	main(int argc, char **argv)
{
	t_window	img;
	t_env		this;
	t_map		*map;
	t_mat4		op_matrix;
	t_trig_lookup	cache;
	t_trans_vals	obj;
	int		i;

	if (argc != 2)
	{
		perror("Error: Invalid number of arguments");
		return (-1);
	}
	this.mlx = mlx_init();
	this.mlx_win = mlx_new_window(this.mlx, MAX_WIDTH, MAX_HEIGHT, "WINWINWIN");
	img.img = mlx_new_image(this.mlx, MAX_WIDTH, MAX_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (init_map(argv[1], &map))
		return (mlx_destroy_window(this.mlx, this.mlx_win));
	init_vals(&obj);
	init_tables(&cache);
	ft_pipeline(&op_matrix, obj, &cache);
	i = 0;
	while (i < map->num_points)
	{
		printf("%f, %f, %f\n",map->points[i].x, map->points[i].y, map->points[i].z); 
		apply_transform(&map->points[i], &op_matrix);
		printf("%f, %f, %f",map->points[i].x, map->points[i].y, map->points[i].z); 
		printf("\n\n");
		i++;
	}
	/*
	int i = 0;
	printf("(x), (y), (z)\n\n");
	while (i < map->num_points)
	{
		printf("%f, %f, %f\n", map->points[i].x, map->points[i].y, map->points[i].z);
		i++;
	}
	*/
	ft_connect(&img, map);
	mlx_put_image_to_window(this.mlx, this.mlx_win, img.img, 0, 0);
	mlx_loop(this.mlx);
}
