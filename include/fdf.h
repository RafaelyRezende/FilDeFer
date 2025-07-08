/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:14:59 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/07 12:14:30 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 1980
# define HEIGTH 1080

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
	int	x;
	int	y;
}	t_point;

typedef	struct s_env_vars
{
	void		*mlx;
	void		*mlx_win;
	t_window	windows;
	t_vec3		mat;
}	t_env_vars;

void	ft_put_pixel(t_window *window, int width, int heigth, int color);
void	ft_swap(int *a, int *b);
void	ft_init_line(t_line *line, t_point p1, t_point p2);
t_vec3	*ft_parser(char *av);
t_vec3	ft_constructor(int xval, int yval);
#endif
