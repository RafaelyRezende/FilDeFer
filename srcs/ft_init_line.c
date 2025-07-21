/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:50:13 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/21 14:19:58 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_line(t_line *line, t_vec4 p1, t_vec4 p2)
{
	line->dx = fabs(p2.x - p1.x);
	line->dy = fabs(p2.y - p1.y);
	line->two_dy = 2 * line->dy;
	line->param = line->two_dy - line->dx;
}
