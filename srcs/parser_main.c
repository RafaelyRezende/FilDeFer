#include "fdf.h"
#include <stdio.h>

extern 
int	init_map(const char*, t_map *);

static
int	ft_error(int status)
{
	if (status < 0)
	{
		ft_printf("Error...");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	status;
	int	i;
	t_map	map;

	if (argc != 2)
		return (-1);
	map.mapCol = -1;
	map.mapRow = 0;
	status = init_map(argv[1], &map);
	if (status)
		return(ft_error(status));
/*	ft_printf("ROWS:\t(%d), COLS:\t(%d)\n\n\n", map.mapRow, map.mapCol);
	i = 0;
	ft_printf("(x), (y), (z)\n");
	while (i < map.num_points)
	{
		printf("(%f), (%f), (%f)\n", map.points[i].x, map.points[i].y, map.points[i].z);
		i++;
	}*/
	free(map.points);
	return (0);
}
