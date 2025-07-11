/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:51:22 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/10 16:40:56 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# define COLOR1 0x88FFFF00
# define COLOR2 0x00FF00FF

static void	ft_draw_line(t_window *img, t_point p1, t_point p2, t_line l1)
{
	int	p0;
	int	inc_x;
	int	inc_y;

	if (p1.x > p2.x)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
	}
	p0 = l1.param;
	inc_y = 1;
	if (p1.y > p2.y)
		inc_y = -1;
	inc_x = 1;
	if (p1.x > p2.x)
		inc_x = -1;
	ft_put_pixel(img, p1.x, p1.y, COLOR1);
	while (p1.x < p2.x)
	{
		if (p0 < 0)
			p0 += l1.two_dy;
		else
		{
			p1.y += inc_y;
			p0 += l1.two_dy - 2 * l1.dx;
		}
		p1.x += inc_x;
		ft_put_pixel(img, p1.x, p1.y, COLOR1);
	}
}

static void	ft_draw_line_too(t_window *img, t_point p1, t_point p2, t_line l1)
{
	int	p0;
	int	inc_x;
	int	inc_y;

	if (p1.y > p2.y)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
	}
	p0 = 2 * l1.dx - l1.dy;
	inc_y = 1;
	if (p1.y > p2.y)
		inc_y = -1;
	inc_x = 1;
	if (p1.x > p2.x)
		inc_x = -1;
	ft_put_pixel(img, p1.x, p1.y, COLOR1);
	while (p1.y < p2.y)
	{
		if (p0 < 0)
			p0 += 2 * l1.dx;
		else
		{
			p1.x += inc_x;
			p0 += 2 * l1.dx - l1.two_dy;
		}
		p1.y += inc_y;
		ft_put_pixel(img, p1.x, p1.y, COLOR1);
	}
}

static void	ft_draw_edge(t_window *img, t_point p1, t_point p2)
{
	t_line	l1;

	ft_init_line(&l1, p1, p2);
	if (l1.dy > l1.dx)
		ft_draw_line_too(img, p1, p2, l1);
	else
		ft_draw_line(img, p1, p2, l1);
	return ;
}

int	main(void)
{
	t_env_vars	this;
	t_window		img;
	//t_vec3		*map;

	t_point		p0;
	t_point		p1;
	t_point		p2;
	t_point		p3;
	t_point		p4;
	t_point		p5;
	t_point		p6;
	t_point		p7;
	t_point		p8;

	//map = ft_parser(argv[1]);
	this.mlx = mlx_init();
	this.mlx_win = mlx_new_window(this.mlx, WIDTH, HEIGTH, "WINWINWIN");
	img.img = mlx_new_image(this.mlx, WIDTH, HEIGTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	p0.x = WIDTH / 2;
	p0.y = HEIGTH / 2;

	p1.x = p0.x + 200;
	p1.y = p0.y + 50;

	p2.x = p0.x + 50;
	p2.y = p0.y + 200;

	p3.x = p0.x - 50;
	p3.y = p0.y + 200;

	p4.x = p0.x - 200;
	p4.y = p0.y + 50;

	p5.x = p0.x - 200;
	p5.y = p0.y - 50;

	p6.x = p0.x - 50;
	p6.y = p0.y - 200;

	p7.x = p0.x + 50;
	p7.y = p0.y - 200;
	
	p8.x = p0.x + 200;
	p8.y = p0.y - 50;

	ft_draw_edge(&img, p0, p1);
	ft_draw_edge(&img, p0, p2);
	ft_draw_edge(&img, p0, p3);
	ft_draw_edge(&img, p0, p4);
	ft_draw_edge(&img, p0, p5);
	ft_draw_edge(&img, p0, p6);
	ft_draw_edge(&img, p0, p7);
	ft_draw_edge(&img, p0, p8);
	mlx_put_image_to_window(this.mlx, this.mlx_win, img.img, 0, 0);
	mlx_loop(this.mlx);
}
