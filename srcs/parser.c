/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/19 15:46:05 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_free_line(int fd, char *line)
{
	free(line);
	close(fd);
	return (-1);
}

int	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (-1);
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (-1);
}

int	ft_count_col(char *line, int *col)
{
	char	**split;
	int		count;

	count = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	while (split[count])
		count++;
	if (*col < 0)
		*col = count;
	else if (count != *col)
		return (ft_free_split(split));
	return (!(ft_free_split(split)));
}

int	ft_get_dim(const char *filename, int *row, int *col)
{
	int		fd;
	int		status;
	char	*line;

	*row = 0;
	*col = -1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		status = ft_count_col(line, col);
		free(line);
		if (status < 0)
		{
			close(fd);
			return (-1);
		}
		(*row)++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	init_map(const char *filename, t_map *map, t_mat4 *quat)
{
	int				fd;
	char			*line;
	char			**split;
	t_map_dimension	map_dim;
	t_trig_lookup	cache;

	if (ft_get_dim(filename, &map_dim.mapRow, &map_dim.mapCol) < 0)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	map->num_points = map_dim.mapRow * map_dim.mapCol;
	map->points = malloc(sizeof(t_vec4) * map->num_points);
	init_tables(&cache);
	fd = open(filename, O_RDONLY);
	if (!fd)
		return (-1);
}

/*
static int	ft_free_vec(t_vec3 *matrix)
{
	if (matrix)
	{
		if (matrix->x_i)
			free(matrix->x_i);
		if (matrix->y_i)
			free(matrix->y_i);
		if (matrix->z_i)
			free(matrix->z_i);
	}
	free(matrix);
	return (0);
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
	while (gnl)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(str);
	matrix->ncols = i;
	if (close(fd) == -1 || i < 0)
		return (0);
	return (i);
}

static int	ft_init_coord(t_vec3 *matrix)
{
	int	numE;

	numE = matrix->nrows * matrix->ncols;
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
	while (i < matrix->nrows)
	{
		j = 0;
		buffer = ft_split(str, ' ');
		free(str);
		if (!buffer)
			return (0);
		while (buffer[j] && j < matrix->ncols)
		{
			matrix->x_i[j + i * matrix->ncols] = j;
			matrix->y_i[j + i * matrix->ncols] = i;
			matrix->z_i[j + i * matrix->ncols] = ft_atoi(buffer[j]); 
			free(buffer[j]);
			j++;
		}
		while (buffer[j])
			free(buffer[j++]);
		str = get_next_line(fd);
		i++;
		free(buffer);
	}
	free(str);
	return (i);
}

t_vec3	*ft_parser(char *av)
{
	t_vec3	*map;
	int	fd;

	map = (t_vec3 *) malloc(sizeof(t_vec3));
	map->nrows = ft_get_rows(map, av);
	map->ncols = ft_get_cols(map, av);
	if (!ft_init_coord(map))
		return (NULL);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!ft_fill_matrix(fd, map))
		return (ft_free_vec(map), NULL);
	close(fd);
	return (map);
}

int	main(void)
{
	char	*ptr;
	t_vec3	*matrix;
	int	i;
	int	numE;

	i = 0;
	ptr = "test_maps/test.fdf";
	matrix = ft_parser(ptr);
	numE = matrix->nrows * matrix->ncols;
	while (i < numE)
	{
		printf("x: %d, ", matrix->x_i[i]);
		printf("y: %d, ", matrix->y_i[i]);
		printf("z: %d", matrix->z_i[i]);
		printf("\n");
		i++;
	}
	return (ft_free_vec(matrix));
}
*/
