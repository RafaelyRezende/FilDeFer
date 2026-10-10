/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (review fixes: L-05, L-06, L-07)             */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

/*
** L-07 fix: validate tokens before atoi. Accepts an optional sign followed
** by at least one digit, plus the fdf-standard optional ",0xRRGGBB" color
** suffix. Anything else rejects the map instead of silently becoming 0.
*/
static
int	ft_ishexdigit(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || \
(c >= 'A' && c <= 'F'));
}

static
int	ft_valid_token(const char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	if (!ft_isdigit(*s))
		return (0);
	while (ft_isdigit(*s))
		s++;
	if (*s == ',')
	{
		s++;
		if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
			s += 2;
		if (!ft_ishexdigit(*s))
			return (0);
		while (ft_ishexdigit(*s))
			s++;
	}
	return (*s == '\0' || *s == '\n');
}

/*
** L-05/L-06 fix: on any failure after allocation, free the partial map and
** reset *map to NULL so callers never touch a dangling pointer. Rejects
** empty or degenerate maps (rows/cols <= 0) here, and guards the
** rows * cols product against size_t overflow before allocating the grid.
*/
static
int	ft_mapalloc(const char *filename, t_map **map)
{
	size_t	total;

	*map = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!*map)
		return (-1);
	(*map)->rows = 0;
	(*map)->cols = -1;
	if ((ft_get_dim(filename, &((*map)->rows), &((*map)->cols)) < 0) || \
(*map)->rows <= 0 || (*map)->cols <= 0)
	{
		free(*map);
		*map = NULL;
		return (-1);
	}
	total = (size_t)(*map)->rows * (size_t)(*map)->cols;
	if (total > SIZE_MAX / sizeof(t_point))
	{
		free(*map);
		*map = NULL;
		return (-1);
	}
	(*map)->size = (unsigned int)total;
	(*map)->grid = ft_calloc(sizeof(t_point), (*map)->size);
	if (!(*map)->grid)
	{
		free(*map);
		*map = NULL;
		return (-1);
	}
	if (ft_init_order(*map) < 0)
	{
		free((*map)->grid);
		free(*map);
		*map = NULL;
		return (-1);
	}
	return (0);
}

/*
** L-07 fix: plain j = 0 loop (no unsigned wrap-around trick); each line
** must yield exactly cols tokens, and the write index is bounded by size,
** so a malformed file can never overrun the grid buffer.
*/
static
int	ft_parse_grid(int fd, t_map **map)
{
	char			*line;
	char			**split;
	unsigned int	i;
	int				j;

	i = 0;
	while (i < (*map)->size)
	{
		line = get_next_line(fd);
		if (!line)
			return (-1);
		split = ft_split(line, ' ');
		free(line);
		if (!split)
			return (-1);
		j = 0;
		while (split[j] && i < (*map)->size)
		{
			if (!ft_valid_token(split[j]))
				return (ft_free_split(split));
			(*map)->grid[i].x_ori = (float) j;
			(*map)->grid[i].z_ori = (float) ft_atoi(split[j]);
			(*map)->grid[i].y_ori = (float)(i / (unsigned int)(*map)->cols);
			i++;
			j++;
		}
		if (j != (*map)->cols)
			return (ft_free_split(split));
		(void)ft_free_split(split);
	}
	return (0);
}

/*
** L-05 fix: the fd is closed on every path (success, alloc failure, parse
** failure). Previously it leaked on both error paths and on success.
*/
int	init_map(const char *filename, t_map **map)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	if ((ft_mapalloc(filename, map)) < 0)
	{
		close(fd);
		return (-1);
	}
	if (ft_parse_grid(fd, map))
		return (ft_free_map(fd, map));
	close(fd);
	return (0);
}
