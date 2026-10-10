/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:52:12 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/10/10 by jps (review fix: P-07 overflow guard)           */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** P-07 fix: signature upgraded to size_t (matching libc calloc) and the
** nmemb * size product is overflow-checked before allocation. Without the
** guard, a huge grid request could wrap the product, under-allocate, and
** later writes would corrupt the heap.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > ((size_t) -1) / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
