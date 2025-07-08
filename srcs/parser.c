/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:14:58 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/07 19:20:00 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vec3	*vals;
	if (argc != 2)
		return (-1);
	vals = ft_parser(argv[1]);
	free(vals->x_i);
	free(vals->y_i);
	free(vals->z_i);
	free(vals);
}
