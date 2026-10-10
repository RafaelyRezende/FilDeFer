#include "iso_fdf.h"

t_vec3	ft_vec3_constructor(float x, float y, float z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

/*
** P-06 fix: guard against normalizing a (near-)zero vector — previously a
** division by zero waiting to happen for any caller other than the
** hardcoded (0,0,1) axis.
*/
t_vec3	ft_vec3_norm(t_vec3 u)
{
	float	len;

	len = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
	if (len < 1e-8f)
		return (ft_vec3_constructor(0.0f, 0.0f, 0.0f));
	return (ft_vec3_scale(u, 1.0f / len));
}

/*
** P-06 fix: `inline` qualifiers removed. Under -std=gnu89 a plain inline
** emits no standalone definition, so the program only linked because the
** optimizer happened to inline every call — a latent link failure.
*/
t_vec3	ft_vec3_add(t_vec3 u, t_vec3 v)
{
	return (ft_vec3_constructor((u.x + v.x), (u.y + v.y), (u.z + v.z)));
}

t_vec3	ft_vec3_sub(t_vec3 u, t_vec3 v)
{
	return (ft_vec3_constructor((u.x - v.x), (u.y - v.y), (u.z - v.z)));
}

t_vec3	ft_vec3_scale(t_vec3 u, float scaler)
{
	return (ft_vec3_constructor((u.x * scaler), \
(u.y * scaler), (u.z * scaler)));
}
