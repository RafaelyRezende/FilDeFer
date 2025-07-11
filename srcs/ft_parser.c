/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/11 18:55:39 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

// LEAKS ON LEAKS
//

static void	ft_free_vec(t_vec3 *matrix)
{
	if (matrix)
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

static int	ft_get_rows(t_vec3 *matrix, char *av)
{
	char	*str;
	int	i;
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	str = get_next_line(fd);
	if (!str)
		return (free(str),0);
	i = 0;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i++;
	}
	free(str);
	matrix->nrows = i;
	if (close(fd) == -1)
		return (0);
	return (i);
}

static int	ft_get_cols(t_vec3 *matrix, char *av)
{
	char	**str;
	char	*gnl;
	int	fd;
	int	i;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	gnl = get_next_line(fd);
	str = ft_split(gnl, ' ');
	while (str && str[i])
		free(str[i++]);
	i--;
	free(str);
	free(gnl);
	matrix->ncols = i;
	if (close(fd) == -1 || i < 0)
		return (0);
	return (i);
}

static int	ft_init_coord(t_vec3 *matrix)
{
	int	numE;

	numE= matrix->nrows * matrix->ncols;
	matrix->x_i = (int *)malloc(sizeof(int) * numE);
	if (!matrix->x_i)
		return (0);
	matrix->y_i = (int *)malloc(sizeof(int) * numE);
	if (!matrix->y_i)
		return (free(matrix->x_i), 0);
	matrix->z_i = (int *)malloc(sizeof(int) * numE);
	if (!matrix->z_i)
	{
		free(matrix->x_i);
		return (free(matrix->y_i), free(matrix->z_i), 0);
	}
	return (1);
}

static int	ft_fill_matrix(int fd, t_vec3 *matrix)
{
	char	*str;
	char	**buffer;
	int	numE;
	int	i;
	int	j;

	numE = matrix->nrows * matrix->ncols;
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		j = 0;
		buffer = ft_split(str);
		if (!buffer)
			return (free(str), 0);
		free(str);
		while (buffer[j])
		{
			matrix->x_i[i + j * numE] = i;
			matrix->y_i[i + j * numE] = j;
			matrix->z_i[i + j * numE] = buffer[j]; 
			free(buffer[j]);
			j++
		}
		i++;
	}
	free(str);
}

t_vec3	*ft_parser(char *av)
{
	t_vec3	*map;
	int	i;
	int	j;

	map = (t_vec3 *) malloc(sizeof(t_vec3));
	map->nrows = ft_get_rows(&map, av);
	map->ncols = ft_get_cols(&map, av);
	if (!ft_init_coord(&map))
		return (NULL);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!ft_fill_matrix(fd, &matrix))
		return (ft_free_vec);
	close(fd);
	free(buffer);
	return (map);
}

int	main(void)
{
	char	*ptr;
	t_vec3	matrix;

	ptr = "test_maps/10-2.fdf";
	printf("%d\n", ft_get_rows(&matrix, ptr));
	printf("%d\n", ft_get_cols(&matrix, ptr));
}

