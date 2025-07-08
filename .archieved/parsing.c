/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:01:05 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/02 15:42:48 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(int argc, char **argv)
{
	int	fd;
	char	*str;
	char	**splitted;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	if (!str)
		return (-1);
	while (*str)
	{
		str = get_next_line(fd);
		if (!str)
			return (-1);
		ft_printf("%s", str);
	}
	splitted = ft_split(str, ' ');
}
