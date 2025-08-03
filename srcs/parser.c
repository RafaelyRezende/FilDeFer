/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/03 16:50:40 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
int	ft_free_line(char *line)
{
	free(line);
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
int	ft_free_map(int fd, t_map **map)
{
	free((*map)->grid);
	free(*map);
	close(fd);
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
int	ft_mapalloc(const char *filename, t_map **map)
{
	*map = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!*map)
		return (-1);
	(*map)->rows = 0;
	(*map)->cols = -1;
	if ((ft_get_dim(filename, &((*map)->rows), &((*map)->cols)) < 0))
		return (free(*map), -1);
	(*map)->size = (*map)->rows * (*map)->cols;
	(*map)->grid = ft_calloc(sizeof(t_point), (*map)->size);
	if (!(*map)->grid)
		return (free(*map), -1);
	return (0);
}

static
int	ft_parse_grid(int fd, char *line, char **split, t_map **map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < (*map)->size)
	{
		line = get_next_line(fd);
		if (!line)
			return(ft_free_line(line));
		split = ft_split(line, ' ');
		if (!split)
			return (ft_free_line(line));
		j = -1;
		free(line);
		while (split[++j])
		{
			(*map)->grid[i].x_ori = (float) j;
			(*map)->grid[i].z_ori = (float) (ft_atoi(split[j]));
			(*map)->grid[i].y_ori = (float) (i / (*map)->cols);
			i++;
		}
		(void)ft_free_split(split);
	}
	return (0);
}

int	init_map(const char *filename, t_map **map)
{
	int		fd;
	char	*line;
	char	**split;
	
	line = NULL;
	split = NULL;
	if (ft_mapalloc(filename, map))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (!fd)
		return (ft_free_map(fd, map));
	if (ft_parse_grid(fd, line, split, map))
		return (ft_free_map(fd, map));
	return (0);
}
