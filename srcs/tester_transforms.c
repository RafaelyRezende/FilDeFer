/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_transforms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:33:04 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/24 15:19:24 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_trig_lookup	cache;
	t_trans_vals	obj;
	t_mat4		*rot;
	t_matrix_const	cons;
	t_vec4		q;

	obj.sx = 1.0f;
	obj.sy = 1.0f;
	obj.sz = 1.0f;
	obj.tx = 0.0f;
	obj.ty = 0.0f;
	obj.tz = 0.0f;
	obj.rx = 0.0f;
	obj.ry = 0.0f;
	obj.rz = M_PI/2;

	ft_memset(rot, 0, sizeof(t_mat4));
	init_tables(&cache);
	// Build quat for 90° (π/2) around Z
	q = quat_from_euler(0, 0, M_PI/2, &cache);
	init_cons_mat(q);
	mat4_from_quat(&rot, cons);
	t_vec4 v = {1.0f, 0.0f, 0.0f, 1.0f};
	apply_transform(&v, rot);  // Or use direct quat rotate
	// Expected: approximately (0,1,0)
	 assert(fabs(v.x - 0.0f) < 1e-5);
	 assert(fabs(v.y - 1.0f) < 1e-5);
	 assert(fabs(v.z) < 1e-5);
}
