/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:33:49 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/03 15:20:50 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_v3float v3f_multiply_v(t_v3float u, t_v3float v)
{
	t_v3float out;

	out.x = u.y * v.z - u.z * v.y;
	out.y = u.z * v.x - u.x * v.z;
	out.z = u.x * v.y - u.y * v.x;
	return (out);
}

float
	v3f_dot(t_v3float u, t_v3float v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_v3float
	v3f_add(t_v3float u, t_v3float v)
{
	u.x += v.x;
	u.y += v.y;
	u.z += v.z;
	return (u);
}

t_v3float
	v3f_substract_v(t_v3float u, t_v3float v)
{
	u.x -= v.x;
	u.y -= v.y;
	u.z -= v.z;
	return (u);
}

t_v3float
	v3f_multiply_x(t_v3float u, float n)
{
	u.x *= n;
	u.y *= n;
	u.z *= n;
	return (u);
}

t_v3float
	v3f_divide_x(t_v3float u, float n)
{
	u.x /= n;
	u.y /= n;
	u.z /= n;
	return (u);
}

float v3f_dist_lp(t_ray line, t_v3float point)
{
	t_v3float dir;

	dir = new_v3f(line.origin.x - point.x,
	line.origin.y - point.z,
	line.origin.z - point.z);
	return(v3f_magnitude(v3f_multiply_v(dir, line.direction)) / v3f_magnitude(line.direction));
}