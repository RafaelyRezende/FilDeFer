/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/09 20:45:18 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

// LEAKS ON LEAKS
//
static t_vec3	*ft_init_vars(int xvals, int yvals, int zvals, int nrows, int ncols)
{
	t_vec3	*matrix;
	int	*xvals;
	int	*yvals;
	int	*zvals;
	int	size;

	size = nrows * ncols;
	matrix = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!matrix)
		return (NULL);
	xvals = (int *)malloc(sizeof(int) * size);
	if (!xvals)
		return (free(matrix), NULL);
	yvals = (int *)malloc(sizeof(int) * size);
	if (!yvals)
		return (free(matrix), free(xvals), NULL);
	zvals = (int *)malloc(sizeof(int) * size);
	if (!zvals)
	{
		free(matrix); 
		return (free(xvals), free(yvals), free(zvals), NULL);
	}
	return (matrix);
}

static void	ft_free_vec(t_vec3 *matrix)
{
	if (*matrix)
	{
		if (!(matrix->x_i))
			free(matrix->x_i);
		if (!(matrix->y_i))
			free(matrix->y_i);
		if (!(matrix->z_i))
			free(matrix->z_i);
	}
	free(matrix);
	return ;
}

t_vec3	*ft_parser(char *av)
{
	t_vec3	*map;
	char	**buffer;
	char	*str;
	int	fd;
	int	i;

	map->x_i = x_vals;
	map->y_i = y_vals;
	map->z_i = z_vals;
	fd = open(av, O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		buffer = ft_split(str, ' ');
		i = 0;
		while (buffer[i])
		{
			x_vals[i] = i;
			y_vals[i] = i;
			z_vals[i] = ft_atoi(buffer[i]);
			i++;
		}
	}
	close(fd);
	free(buffer);
	return (map);
}
