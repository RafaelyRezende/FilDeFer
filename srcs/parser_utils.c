/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/05 11:38:09 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

int	ft_free_line(char *line)
{
	free(line);
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

int	ft_free_map(int fd, t_map **map)
{
	free((*map)->grid);
	free(*map);
	close(fd);
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
	(void)ft_free_split(split);
	return (0);
}

int	ft_get_dim(const char *filename, int *row, int *col)
{
	int		fd;
	int		status;
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
