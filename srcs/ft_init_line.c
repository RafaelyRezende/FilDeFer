/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:50:13 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/06 12:19:52 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_line(t_line *line, t_point p1, t_point p2)
{
	line->dx = abs(p2.x - p1.x);
	line->dy = abs(p2.y - p1.y);
	line->two_dy = 2 * line->dy;
	line->param = line->two_dy - line->dx;
}
