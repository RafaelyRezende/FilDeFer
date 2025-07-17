/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:14:59 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/17 17:52:09 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>

# define COLOR1 0x00FF00FF
# define HEIGHT 1440
# define WIDTH 1080
# define WIN_NAME "WINWINWIN"
# define M_PI 3.14159265358979323846
# define MAT4_DIM 16
# define DIM 4
# define MAT4_IDENTITY_VAL 1.0f
# define RAD_STEP 0.1f
# define RAD_MIN 0.0f
# define RAD_MAX (2.0f * M_PI)
# define TABLE_SIZE ((int)((RAD_MAX - RAD_MIN) / RAD_STEP) + 1)

typedef	struct s_window
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_window;

typedef	struct	s_vec3
{
	int	nrows;
	int	ncols;
	int	*x_i;
	int	*y_i;
	int	*z_i;
}	t_vec3;

typedef	struct	s_line
{
	int	dx;
	int	dy;
	int	two_dy;
	int	param;
}	t_line;

typedef	struct	s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef	struct s_env_vars
{
	void		*mlx;
	void		*mlx_win;
	t_window	windows;
	t_vec3		*mat;
}	t_env_vars;

typedef struct __attribute__((aligned(16)))	s_mat4
{
	float	matrix[MAT4_DIM];
}	t_mat4;

typedef struct	s_quat
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_quat; 

typedef struct	s_map
{ 
	t_point	*points;
	int		num_points;
}	t_map;

typedef struct s_trig_lookup
{
	float	sin_table[TABLE_SIZE];
	float	cos_table[TABLE_SIZE];
}	t_trig_lookup;

typedef struct	s_quaternion_const
{
	float	half_x;
	float   half_y;
	float   half_z;
	float   cx;
	float   sx;
	float   cy;
	float   sy;
	float   cz;
	float   sz;
}	t_quaternion_const;

typedef	struct	s_transform_vals
{
	float	sx;
	float	sy;
	float	sz;
	float	tx;
	float	ty;
	float	tz;
	float	rx;
	float	ry;
	float	rz;
}	t_transform_vals;

void	ft_put_pixel(t_window *window, int width, int heigth, int color);
void	ft_swap(int *a, int *b);
void	ft_init_line(t_line *line, t_point p1, t_point p2);
t_vec3	*ft_parser(char *av);
void	ft_connect(t_window *img, t_vec3 *matrix);
#endif
