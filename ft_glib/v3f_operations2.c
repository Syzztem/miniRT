/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_operations2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 12:23:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/11 12:23:45 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

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

float
	v3f_dist_lp(t_ray line, t_v3float point)
{
	t_v3float dir;

	dir = new_v3f(line.origin.x - point.x,
	line.origin.y - point.z,
	line.origin.z - point.z);
	return (v3f_magnitude(v3f_multiply_v(dir, line.direction))
	/ v3f_magnitude(line.direction));
}
