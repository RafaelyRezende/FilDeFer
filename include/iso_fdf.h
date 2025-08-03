/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_fdf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:37:02 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/03 18:40:07 by rluis-ya         ###   ########.fr       */
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
# include <stdint.h>

# define NAME "FDF"
# define SCREEN_H 1080
# define SCREEN_W 1920
# define SCREEN_X (1920/ 2)
# define SCREEN_Y (1080/ 2) 
//# define M_PI 3.14159265358979323846f
# define ISO_X 0.86602540378f
# define ISO_Y 0.5f
# define ROT_SPEED 0.05f
# define COLOR 0XF2FEFA
# define ANGLE_STEP M_PI * 0.01f
# define TRANS_STEP_X 1.0f
# define TRANS_STEP_Y 0.5f
# define MAX_ZOOM 5.0f
# define MIN_ZOOM 0.2f
# define ZOOM_STEP 0.2f

//-------------------------------LINE CONSTANTS-------------------
typedef struct	s_line
{
	float	dx;
	float	dy;
	float	two_dy;
	float	param;
	float	t;
	int	total_steps;
	int	current_steps;
	int	color;
}	t_line;

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;
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
	float	x_ori;
	float	y_ori;
	float	z_ori;
	float	color;
}	t_point;

typedef struct	s_map
{
	t_point		*grid;
	unsigned int	size;
	int		rows;
	int		cols;
	int		*indices;
}	t_map;
//-------------------------------ENVIRONMENT STRUCTURE-------------
typedef struct	s_window
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_window;

typedef	struct	s_limits
{
	float	x_min;
	float	x_max;
	float	y_min;
	float	y_max;
	float	z_min;
	float	z_max;
}	t_limits;

typedef struct	s_env
{
	void		*mlx;
	void		*mlx_win;
	t_window	window;
	t_map		*map;
	t_quat		q_axis;
	t_limits	limits;
	t_vec3		grid_center;
	float		map_scaler;
	float		max_dim;
	float		zoom_scaler;
	float		base_scaler;
	float		offset_x;
	float		offset_y;
	float		trans_x;
	float		trans_y;
	float		angle;
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
t_vec3	ft_vec3_sub(t_vec3, t_vec3);
t_vec3	ft_vec3_scale(t_vec3, float);
t_vec3	ft_rotate_vector(t_quat, t_vec3);
//-------------------------------MAP FUNCTIONS-------------------------
int	ft_sort_map(t_map*);
int	init_map(const char*, t_map**);
float	ft_vec3_mult(t_vec3, t_vec3);
void	ft_apply_rotation(t_env*);
void	ft_rotate_map(t_env*);
void	ft_set_limits(t_env*);
void	ft_iso(t_env *, t_vec3, unsigned int);
void	ft_get_center(t_env *);
int	ft_display_img(t_env *);
//-------------------------------COLOR FUNCTIONS-------------------------
int	ft_interpolate_color(int, int ,float);
int	ft_height_to_color(t_env *, float);
int	ft_rgb2int(int, int, int);
t_rgb	ft_int2rgb(int);
void	ft_set_color(t_env *);
//-------------------------------SCREEN FUNCTIONS-----------------------
void	ft_put_pixel(t_window *, float, float, float);
void	ft_swap(float*, float*);
void	ft_init_line(t_line *, t_point, t_point);
t_point	*ft_parser(char *);
void	ft_connect(t_window *, t_map *);
//-------------------------------KEYPRESS FUNCTIONS----------------------
int	ft_keypress(int, t_env*);
//-------------------------------GARBAGE COLLECTION----------------------
void	ft_clean_map(t_map *);
void	ft_clear_image(t_window *);
int	ft_clean_exit(t_env *);
#endif
