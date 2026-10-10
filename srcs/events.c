#include "iso_fdf.h"

static
void	ft_button_translate(int key, t_env *this)
{
	if (key == XK_w)
		this->trans_y -= TRANS_STEP_Y;
	if (key == XK_s)
		this->trans_y += TRANS_STEP_Y;
	if (key == XK_a)
		this->trans_x -= TRANS_STEP_X;
	if (key == XK_d)
		this->trans_x += TRANS_STEP_X;
}

/*
** L-08 fix: zoom is clamped AFTER the multiplicative step, so the value
** can never overshoot MAX_ZOOM / MIN_ZOOM (previously 4.9 * 1.1 = 5.39
** slipped past the gate).
*/
static
void	ft_button_scale(int key, t_env *this)
{
	if (key == XK_q)
		this->angle += ANGLE_STEP;
	if (key == XK_e)
		this->angle -= ANGLE_STEP;
	if (key == XK_m)
		this->zoom_scaler = fminf(this->zoom_scaler * ZOOM_IN_FACTOR, MAX_ZOOM);
	if (key == XK_n)
		this->zoom_scaler = fmaxf(this->zoom_scaler * ZOOM_OUT_FACTOR, MIN_ZOOM);
}

static
void	ft_button_toggle(int key, t_env *this)
{
	if (key == XK_equal)
		this->z_scaler += HEIGHT_STEP;
	else if (key == XK_minus)
		this->z_scaler -= HEIGHT_STEP;
	else if (key == XK_2)
		this->is_iso = 0;
	else if (key == XK_1)
		this->is_iso = 1;
}

/*
** L-11 fix: raw numeric keycodes replaced by X11 keysym macros.
** P-04 fix: any state-mutating key raises needs_redraw so the loop hook
** redraws exactly once per change instead of every tick.
*/
int	ft_keypress(int key, void *param)
{
	t_env	*this;

	this = param;
	if (key == XK_Escape)
		ft_clean_exit(this);
	if (key == XK_w || key == XK_s || key == XK_a || key == XK_d)
		ft_button_translate(key, this);
	else if (key == XK_q || key == XK_e || key == XK_m || key == XK_n)
		ft_button_scale(key, this);
	else if (key == XK_equal || key == XK_minus || key == XK_2 || key == XK_1)
		ft_button_toggle(key, this);
	else
		return (0);
	this->needs_redraw = 1;
	return (0);
}
