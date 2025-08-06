/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:11:37 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/08/06 20:03:42 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static inline
float	ft_get_depth(t_point p)
{
	return (p.x_ori + p.y_ori - p.z_ori);
}

static
int	ft_partition(int *indexes, t_point *grid, int low, int high)
{
	float	pivot;
	int		i;
	int		j;
	int		tmp;

	pivot = ft_get_depth(grid[indexes[(low + high) / 2]]);
	i = low - 1;
	j = high + 1;
	while (1)
	{
		i++;
		while (ft_get_depth(grid[indexes[i]]) < pivot)
			i++;
		j--;
		while (ft_get_depth(grid[indexes[j]]) > pivot)
			j--;
		if (i >= j)
			return (j);
		tmp = indexes[i];
		indexes[i] = indexes[j];
		indexes[j] = tmp;
	}
}

static
void	ft_quicksort(int *indexes, t_point *grid, int low, int high)
{
	int	p;

	if (low < high)
	{
		p = ft_partition(indexes, grid, low, high);
		ft_quicksort(indexes, grid, low, p);
		ft_quicksort(indexes, grid, p + 1, high);
	}
}

int	ft_sort_map(t_map *map)
{
	int				*indexes;
	unsigned int	i;

	if (!map || !map->grid || map->size <= 1)
		return (-1);
	indexes = (int *)ft_calloc(map->size, sizeof(int));
	if (!indexes)
		return (-1);
	i = 0;
	while (i < map->size)
	{
		indexes[i] = i;
		i++;
	}
	ft_quicksort(indexes, map->grid, 0, map->size - 1);
	if (map->indexes)
		free(map->indexes);
	map->indexes = indexes;
	return (0);
}
