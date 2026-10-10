/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 by jps (V-01 fix)                               */
/*   Updated: 2026/10/10 by jps                                              */
/*                                                                            */
/* ************************************************************************** */

#include "iso_fdf.h"

/*
** V-01 fix: painter's algorithm for the wireframe.
**
** ft_connect used to rasterize edges in fixed row-major lattice order.
** That order only coincides with back-to-front depth order near the
** initial orientation, so after rotating the model, far geometry was
** painted last and bled over near geometry ("lines written on top of
** each other", perspective looking inside-out). The old `indexes`
** depth-sort subsystem tried to address this but was removed as dead
** code because its result was never consumed by the renderer.
**
** Vertices are now sorted once per frame by the depth key computed in
** ft_iso() (projection onto the view/kernel direction), and ft_connect
** walks map->order. Merge sort is used: O(n log n), stable (equal-depth
** vertices keep lattice order, so frames don't shimmer), and it needs
** no global state, unlike a qsort comparator would.
*/
static
void	ft_merge(t_map *map, unsigned int *tmp, unsigned int lo, \
unsigned int hi)
{
	unsigned int	mid;
	unsigned int	a;
	unsigned int	b;
	unsigned int	k;

	mid = lo + (hi - lo) / 2;
	a = lo;
	b = mid;
	k = lo;
	while (a < mid && b < hi)
	{
		if (map->grid[map->order[a]].depth <= map->grid[map->order[b]].depth)
			tmp[k++] = map->order[a++];
		else
			tmp[k++] = map->order[b++];
	}
	while (a < mid)
		tmp[k++] = map->order[a++];
	while (b < hi)
		tmp[k++] = map->order[b++];
	k = lo;
	while (k < hi)
	{
		map->order[k] = tmp[k];
		k++;
	}
}

static
void	ft_merge_sort(t_map *map, unsigned int *tmp, unsigned int lo, \
unsigned int hi)
{
	unsigned int	mid;

	if (hi - lo < 2)
		return ;
	mid = lo + (hi - lo) / 2;
	ft_merge_sort(map, tmp, lo, mid);
	ft_merge_sort(map, tmp, mid, hi);
	ft_merge(map, tmp, lo, hi);
}

/*
** Sorts map->order back-to-front (ascending depth). If the scratch
** allocation fails, the previous order is kept: the frame still renders
** (with the stale ordering) instead of crashing.
*/
void	ft_sort_order(t_map *map)
{
	unsigned int	*tmp;

	tmp = (unsigned int *)malloc(map->size * sizeof(*tmp));
	if (!tmp)
		return ;
	ft_merge_sort(map, tmp, 0, map->size);
	free(tmp);
}

/*
** Allocates the draw-order array and initializes it to the identity
** permutation (lattice order). Called once from ft_mapalloc; freed by
** ft_free_map / ft_clean_map.
*/
int	ft_init_order(t_map *map)
{
	unsigned int	i;

	map->order = (unsigned int *)ft_calloc(map->size, sizeof(*map->order));
	if (!map->order)
		return (-1);
	i = 0;
	while (i < map->size)
	{
		map->order[i] = i;
		i++;
	}
	return (0);
}
