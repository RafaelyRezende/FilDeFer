/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:14:59 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/19 11:09:57 by rluis-ya         ###   ########.fr       */
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
# define MAX_HEIGHT 1980
# define MAX_WIDTH 1080
# define WINDOW_NAME "WINWINWIN"
# define M_PI 3.14159265358979323846
# define MAT4_DIM 16
# define DIM 4
# define MAT4_IDENTITY_VAL 1.0f
# define RAD_STEP 0.1f
# define RAD_MIN 0.0f
# define RAD_MAX (2.0f * M_PI)
# define TABLE_SIZE ((int)((RAD_MAX - RAD_MIN) / RAD_STEP) + 1)

typedef struct	s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4; 

typedef	struct	s_line
{
	int	dx;
	int	dy;
	int	two_dy;
	int	param;
}	t_line;

typedef struct	s_map_dimension
{
	int	mapRow;
	int	mapCol;
}	t_map_dimension;

typedef struct	s_map
{ 
	t_vec4	*points;
	int		num_points;
}	t_map;

typedef struct __attribute__((aligned(16)))	s_mat4
{
	float	matrix[MAT4_DIM];
}	t_mat4;

typedef struct s_trig_lookup
{
	float	sin_table[TABLE_SIZE];
	float	cos_table[TABLE_SIZE];
}	t_trig_lookup;

typedef struct	s_quat_const
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
}	t_quat_const;

typedef	struct	s_trans_vals
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
}	t_trans_vals;

typedef	struct s_window
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_window;

typedef	struct s_env
{
	void			*mlx;
	void			*mlx_win;
	t_window		windows;
	t_map			*map;
	t_map_dimension	mapDim;
}	t_env;

void	ft_put_pixel(t_window *window, int width, int heigth, int color);
void	ft_swap(int *a, int *b);
void	ft_init_line(t_line *line, t_vec4 p1, t_vec4 p2);
t_vec4	*ft_parser(char *av);
void	ft_connect(t_window *img, t_vec4 *matrix);
#endif
