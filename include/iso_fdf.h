/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_fdf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:37:02 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/28 12:53:25 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISO_FDF_H
#define ISO_FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define NAME "FDF"
# define SCREEN_H 1080
# define SCREEN_W 1920
# define SCREEN_X (800 / 2)
# define SCREEN_Y (1200 / 2) 
# define M_PI 3.14159265358979323846f
# define ISO_X 0.86602540378f
# define ISO_Y 0.5f
# define ROT_SPEED 0.05f
# define COLOR 0XF2FEFA

//-------------------------------LINE CONSTANTS-------------------
typedef struct	s_line
{
	float	dx;
	float	dy;
	float	two_dy;
	float	param;
}	t_line;
//-------------------------------VECTOR STRUCTURE------------------
typedef struct s_vec3	
{
	float	x;
	float	y;
	float	z;
}	t_vec3;
//-------------------------------QUATERNION STRUCTURE---------------
typedef struct	s_quat
{
	float	w;
	float	x;
	float	y;
	float	z;
}	t_quat;
//-------------------------------MAP STRUCTURES--------------------
typedef struct	s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

typedef struct	s_map
{
	t_point				*grid;
	unsigned int		size;
	int					rows;
	int					cols;
	int					*indices;
}	t_map;
//-------------------------------ENVIRONMENT STRUCTURE-------------
typedef struct	s_window
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_window;

typedef struct	s_env
{
	t_map		*map;
	t_window	window;
	t_quat		*q;
	void		*mlx;
	void		*mlx_win;
}	t_env;
//-------------------------------QUATERNIONS FUNCTIONS--------------
t_quat	ft_quat_constructor(float, float, float, float);
t_quat	ft_conjugate(t_quat);
t_quat	ft_quat_mult(t_quat, t_quat);
t_quat	ft_quat_from_angle(t_vec3, float);
//-------------------------------VECTORS FUNCTIONS-------------------
t_vec3	ft_vec3_constructor(float, float, float);
t_vec3	ft_vec3_norm(t_vec3);
t_vec3	ft_vec3_add(t_vec3, t_vec3);
t_vec3	ft_vec3_scale(t_vec3, float);
t_vec3	ft_rotate_vector(t_quat, t_vec3);
//-------------------------------MAP FUNCTIONS-----------------------
void	ft_iso(t_map**, float);
int		ft_sort_map(t_map*);
int		init_map(const char*, t_map**);
float	ft_vec3_mult(t_vec3, t_vec3);
//-------------------------------SCREEN FUNCTIONS-----------------------
void	ft_put_pixel(t_window *, float, float, float);
void	ft_swap(float*, float*);
void	ft_init_line(t_line *, t_point, t_point);
t_point	*ft_parser(char *);
void	ft_connect(t_window *, t_map *);
//-------------------------------KEYPRESS FUNCTIONS-----------------------
int		ft_keypress(int, t_env*);
//-------------------------------SORTING FUNCTIONS-----------------------
#endif
