/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/22 12:41:15 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static
int	ft_free_line(int fd, char *line)
{
	free(line);
	close(fd);
	return (-1);
}

static
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

static
int	ft_count_col(char *line, int *col)
{
	char	**split;
	int	count;

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
	(void)ft_free_split(split);
	return (0);
}

static
int	ft_get_dim(const char *filename, int *row, int *col)
{
	int	fd;
	int	status;
	char	*line;

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

static
int	ft_free_map(t_map *map)
{
	free(map->points);
	return (-1);
}

int	init_map(const char *filename, t_map *map)//, t_mat4 *quat
{
	int	fd;
	int	i;
	int	j;
	char	*line;
	char	**split;

	if ((ft_get_dim(filename, &map->mapRow, &map->mapCol)) < 0)
		return (-1);
	map->num_points = map->mapRow * map->mapCol;
	fd = open(filename, O_RDONLY);
	if (!fd)
		return (-1);
	map->points = malloc(sizeof(t_vec4) * map->num_points);
	if (!map->points)
		return (-1);
	i = 0;
	while (i < map->num_points)
	{
		line = get_next_line(fd);
		if (!line)
			return(free(line),-1);
		split = ft_split(line, ' ');
		if (!split)
			return (ft_free_map(map));
		j = 0;
		free(line);
		while (split[j])
		{
			map->points[i].x = (float) j;
			map->points[i].y = (float) (i / map->mapCol);
			map->points[i].z = (float) (ft_atoi(split[j]));
			map->points[i].w = 0.0f;
			j++;
			i++;
		}
		(void)ft_free_split(split);
	}
	return (0);
}
