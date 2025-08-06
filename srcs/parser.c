/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/06 20:51:04 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static
int	ft_mapalloc(const char *filename, t_map **map)
{
	*map = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!*map)
		return (-1);
	(*map)->rows = 0;
	(*map)->cols = -1;
	if ((ft_get_dim(filename, &((*map)->rows), &((*map)->cols)) < 0))
		return (-1);
	(*map)->size = (*map)->rows * (*map)->cols;
	(*map)->grid = ft_calloc(sizeof(t_point), (*map)->size);
	if (!(*map)->grid)
		return (-1);
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
			return (ft_free_line(line));
		split = ft_split(line, ' ');
		if (!split)
			return (ft_free_line(line));
		j = -1;
		free(line);
		while (split[++j])
		{
			(*map)->grid[i].x_ori = (float) j;
			(*map)->grid[i].z_ori = (float) ft_atoi(split[j]);
			(*map)->grid[i].y_ori = (float) i / (*map)->cols;
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
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	if ((ft_mapalloc(filename, map)) < 0)
		return (-1);
	if (ft_parse_grid(fd, line, split, map))
			return (ft_free_map(fd, map));
	return (0);
}
