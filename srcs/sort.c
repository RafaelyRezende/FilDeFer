/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:11:37 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/28 12:58:45 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

static inline
float	ft_get_depth(t_point p)
{
	return (p.x + p.y + p.z);
}

static
int	ft_partition(int *indices, t_point *grid, int low, int high)
{
	float	pivot;
	int		i;
	int		j;
	int		tmp;

	pivot = ft_get_depth(grid[indices[(low + high) / 2]]);
	i = low - 1;
	j = high + 1;
	while (1)
	{
		i++;
		while (ft_get_depth(grid[indices[i]]) > pivot)
			i++;
		j--;
		while (ft_get_depth(grid[indices[j]]) < pivot)
			j--;
		if (i >= j)
			return (j);
		tmp = indices[i];
		indices[i] = indices[j];
		indices[j] = tmp;
	}
}

static
void	ft_quicksort(int *indices, t_point *grid, int low, int high)
{
	int	p;

	if (low < high)
	{
		p = ft_partition(indices, grid, low, high);
		ft_quicksort(indices, grid, low, p);
		ft_quicksort(indices, grid, p + 1, high);
	}
}

int	ft_sort_map(t_map *map)
{
	int				*indices;
	unsigned int	i;

	if (!map || !map->grid || map->size <= 1)
		return (-1);
	indices = (int *)ft_calloc(map->size, sizeof(int));
	if (!indices)
		return (-1);
	i = 0;
	while (i < map->size)
	{
		indices[i] = i;
		i++;
	}
	ft_quicksort(indices, map->grid, 0, map->size - 1);
	map->indices = indices;
	return (0);
}
