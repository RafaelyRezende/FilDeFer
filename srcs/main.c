#include "iso_fdf.h"

static
int	ft_error(const char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

static
void	ft_init_env(t_env *this)
{
	this->mlx = NULL;
	this->mlx_win = NULL;
	this->map = NULL;
	this->window.img = NULL;
	this->window.addr = NULL;
	this->needs_redraw = 1;
}

/*
** L-03 fix: validate against the LAST dot (ft_strrchr) and require it to
** come after the last path separator, so directories containing dots no
** longer cause false rejections. Prints usage and exits non-zero instead
** of a silent exit(0).
*/
static
void	ft_checker_path(char *path)
{
	char	*dot;
	char	*slash;

	dot = ft_strrchr(path, '.');
	slash = ft_strrchr(path, '/');
	if (!dot || (slash && dot < slash) || ft_strcmp(dot, ".fdf") != 0)
	{
		ft_putstr_fd("Usage: ./fdf <map.fdf>\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_env	this;

	if (argc != 2)
		return (ft_error("usage: ./fdf <map.fdf>"));
	ft_checker_path(argv[1]);
	ft_init_env(&this);
	this.mlx = mlx_init();
	if (!this.mlx)
		return (ft_error("mlx_init failed (is DISPLAY set?)"));
	this.mlx_win = mlx_new_window(this.mlx, SCREEN_W, SCREEN_H, NAME);
	this.window.img = mlx_new_image(this.mlx, SCREEN_W, SCREEN_H);
	if (!this.mlx_win || !this.window.img)
		return (ft_fail_exit(&this));
	this.window.addr = mlx_get_data_addr(this.window.img, \
&this.window.bits_per_pixel, &this.window.line_length, &this.window.endian);
	if (!this.window.addr)
		return (ft_fail_exit(&this));
	if ((init_map(argv[1], &this.map)) < 0)
		return (ft_fail_exit(&this));
	ft_get_center(&this);
	mlx_loop_hook(this.mlx, ft_display_img, &this);
	mlx_hook(this.mlx_win, 2, 1L << 0, ft_keypress, &this);
	mlx_hook(this.mlx_win, 17, 1L << 17, ft_clean_exit, &this);
	mlx_loop(this.mlx);
	return (0);
}
