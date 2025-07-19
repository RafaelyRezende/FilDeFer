#include "fdf.h"

extern int	ft_get_dim(char *, int*, int*);

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
	if (argc != 2)
		return (-1);
	t_map_dimension	map_dim;
	int				status;

	status = ft_get_dim(argv[1], &map_dim.mapRow, &map_dim.mapCol);
	if (status)
		return(ft_error(status));
	ft_printf("rows (%d), cols (%d)\n", map_dim.mapRow, map_dim.mapCol);
}
