/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:33:49 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/10 15:46:14 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_v3double
	v3f_cross(t_v3double u, t_v3double v)
{
	t_v3double out;

	out.x = u.y * v.z - u.z * v.y;
	out.y = u.z * v.x - u.x * v.z;
	out.z = u.x * v.y - u.y * v.x;
	return (out);
}

double
	v3f_dot(t_v3double u, t_v3double v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_v3double
	v3f_add(t_v3double u, t_v3double v)
{
	u.x += v.x;
	u.y += v.y;
	u.z += v.z;
	return (u);
}

t_v3double
	v3f_rotate(t_v3double in, t_v3double axe, double a_sin, double a_cos)
{
	t_v3double	out;

	if (a_cos == 10)
		return (v3f_multiply(in, -1));
	if (isnan(axe.x))
		return (in);
	out.x = in.x * (axe.x * axe.x * (1 - a_cos) + a_cos) +
			in.y * (axe.x * axe.y * (1 - a_cos) - axe.z * a_sin) +
			in.z * (axe.x * axe.z * (1 - a_cos) + axe.y * a_sin);
	out.y = in.x * (axe.x * axe.y * (1 - a_cos) + axe.z * a_sin) +
			in.y * (axe.y * axe.y * (1 - a_cos) + a_cos) +
			in.z * (axe.y * axe.z * (1 - a_cos) - axe.x * a_sin);
	out.z = in.x * (axe.x * axe.z * (1 - a_cos) - axe.y * a_sin) +
			in.y * (axe.y * axe.z * (1 - a_cos) + axe.x * a_sin) +
			in.z * (axe.z * axe.z * (1 - a_cos) + a_cos);
	return (out);
}

t_v3double
	v3f_sub(t_v3double u, t_v3double v)
{
	u.x -= v.x;
	u.y -= v.y;
	u.z -= v.z;
	return (u);
}
