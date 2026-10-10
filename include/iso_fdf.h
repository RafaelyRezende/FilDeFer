/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_fdf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:37:02 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (SDL2/WebAssembly port — minilibx removed)  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISO_FDF_H
# define ISO_FDF_H

# include "libft.h"
# include <SDL.h>
# include <SDL_ttf.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <float.h>

# define NAME "FDF"
# define DEFAULT_H 1080
# define DEFAULT_W 1920
# define ISO_X 0.86602540378f
# define ISO_Y 0.5f
# define ROT_SPEED 0.05f
# define COLOR 0XF2FEFA
# define ANGLE_STEP 0.03141592653f
# define TRANS_STEP_X 1.0f
# define TRANS_STEP_Y 0.5f
# define HEIGHT_STEP 0.1f
# define MAX_ZOOM 5.0f
# define MIN_ZOOM 0.2f
# define ZOOM_IN_FACTOR 1.1f
# define ZOOM_OUT_FACTOR 0.9f
# define MIN_DIM_EPSILON 0.0001f

/*
** Integer Bresenham state (P-05: was float-based with epsilon loop tests).
** dx >= 0, dy <= 0 by construction; err drives the all-octant stepper.
*/
typedef struct s_line
{
	int		dx;
	int		dy;
	int		inc_x;
	int		inc_y;
	int		err;
	int		x1;
	int		y1;
	int		total_steps;
	int		current_steps;
	float	t;
	int		color;
}	t_line;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_quat
{
	float	w;
	float	x;
	float	y;
	float	z;
}	t_quat;

/*
** L-10 fix: color is now int (packed 0xRRGGBB); was float.
** V-01 fix: depth is the per-frame painter's-algorithm key. It is the
** dot product of the rotated model-space point with the view (kernel)
** direction of the projection, computed in ft_iso.
*/
typedef struct s_point
{
	float	x;
	float	y;
	float	x_ori;
	float	y_ori;
	float	z_ori;
	float	depth;
	int		color;
}	t_point;

/*
** V-01 fix: `order` holds vertex indices sorted back-to-front by depth.
** It replaces the old `indexes` subsystem, which was removed as dead code
** precisely because the renderer never consumed it — the fixed row-major
** draw order in ft_connect is what made rotated frames paint far geometry
** over near geometry. ft_connect now walks `order`.
*/
typedef struct s_map
{
	t_point			*grid;
	unsigned int	*order;
	unsigned int	size;
	int				rows;
	int				cols;
}	t_map;

/*
** SDL2 port: replaces the minilibx image descriptor. `addr` is a
** contiguous w*h Uint32 CPU framebuffer owned by us (no line_length /
** bits_per_pixel / endian fields anymore); it is uploaded each frame to
** the streaming ARGB8888 texture.
*/
typedef struct s_window
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	unsigned int	*addr;
	int				w;
	int				h;
}	t_window;

typedef struct s_limits
{
	float	x_min;
	float	x_max;
	float	y_min;
	float	y_max;
	float	z_min;
	float	z_max;
}	t_limits;

/*
** P-04 fix: needs_redraw dirty flag gates the frame redraw.
** SDL2 port: the minilibx display/window pointers are replaced by the
** embedded t_window; `running`
** drives the main loop; font/ui_tex hold the cached controls overlay;
** map_files/map_count/map_index drive Tab map cycling and SDL_DROPFILE.
*/
typedef struct s_env
{
	t_window		window;
	t_map			*map;
	t_quat			q_axis;
	t_limits		limits;
	t_vec3			grid_center;
	float			map_scaler;
	float			max_dim;
	float			zoom_scaler;
	float			base_scaler;
	float			z_scaler;
	float			offset_x;
	float			offset_y;
	float			trans_x;
	float			trans_y;
	float			angle;
	int				is_iso;
	int				needs_redraw;
	int				running;
	TTF_Font		*font;
	SDL_Texture		*ui_tex;
	int				ui_tex_w;
	int				ui_tex_h;
	int				map_index;
	char			**map_files;
	int				map_count;
}	t_env;

t_quat	ft_quat_constructor(float w, float x, float y, float z);
t_quat	ft_conjugate(t_quat q);
t_quat	ft_quat_mult(t_quat a, t_quat b);
t_quat	ft_quat_norm(t_quat q);
t_quat	ft_quat_from_angle(t_vec3 axis, float angle);
t_vec3	ft_vec3_constructor(float x, float y, float z);
t_vec3	ft_vec3_norm(t_vec3 u);
t_vec3	ft_vec3_add(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_sub(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_scale(t_vec3 u, float scaler);
t_vec3	ft_rotate_vector(t_quat q, t_vec3 u);
int		init_map(const char *filename, t_map **map);
int		ft_frame(void *param);
int		ft_count_col(char *line, int *col);
int		ft_get_dim(const char *filename, int *row, int *col);
void	ft_apply_rotation(t_env *env);
void	ft_rotate_map(t_env *env);
void	ft_set_limits(t_env *env);
void	ft_screen_offset(t_env *env);
void	ft_iso(t_env *env, t_vec3 rotated, unsigned int i);
void	ft_get_center(t_env *env);
int		ft_init_order(t_map *map);
void	ft_sort_order(t_map *map);
int		ft_interpolate_color(int color1, int color2, float t);
int		ft_height_to_color(t_env *env, float z);
int		ft_rgb2int(int red, int green, int blue);
t_rgb	ft_int2rgb(int color);
void	ft_set_color(t_env *env);
void	ft_put_pixel(t_window *window, int x, int y, int color);
void	ft_init_line(t_line *line, int x0, int y0, int x1, int y1);
void	ft_connect(t_window *img, t_map *map);
int		ft_keypress(SDL_Keycode key, void *param);
void	ft_clean_map(t_map *map);
void	ft_clear_image(t_window *window);
int		ft_clean_exit(void *param);
int		ft_fail_exit(void *param);
void	ft_shutdown(t_env *env);
int		ft_free_line(char *line);
int		ft_free_split(char **arr);
int		ft_free_map(int fd, t_map **map);

/* SDL2 platform layer (srcs/platform.c) */
int		ft_platform_init(t_env *env, const char *title, int w, int h);
void	ft_platform_events(t_env *env);
void	ft_platform_present(t_env *env);
void	ft_platform_resize(t_env *env, int w, int h);
void	ft_platform_quit(t_env *env);
int		ft_load_map_file(t_env *env, const char *path);
void	ft_cycle_map(t_env *env);

/* SDL2_ttf controls overlay (srcs/font.c), failures non-fatal */
void	ft_ui_init(t_env *env);
void	ft_ui_destroy(t_env *env);
#endif
