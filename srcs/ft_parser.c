/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:01:47 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/08 14:14:43 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

// LEAKS ON LEAKS
//
t_vec3	*ft_parser(char *av)
{
	t_vec3	*map;
	int	*x_vals;
	int	*y_vals;
	int	*z_vals;
	char	**buffer;
	char	*str;
	int	fd;
	int	i;

	map = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!map)
		return (NULL);
	x_vals = (int *) malloc(sizeof(int)*9);
	if (!x_vals)
		return (NULL);
	y_vals = (int *) malloc(sizeof(int)*9);
	if (!y_vals)
		return (NULL);
	z_vals = (int *) malloc(sizeof(int)*9);
	if (!z_vals)
		return (NULL);
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
	while (i >= 0)
	{
		i--;
		free(buffer[i]);
	}
	free(buffer);
	return (map);
}
