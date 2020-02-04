/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:36:59 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/04 13:32:46 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float
	plane_intersecton(t_plane plane, t_ray line)
{
	float d;

	d = v3f_dot(line.direction, plane.normal);
	if (fabsf(d) < EPSILON)
		return (nan(""));
	d = v3f_dot(v3f_sub(plane.p, line.origin), plane.normal) / d;
	return (d);
	return (d > EPSILON ? d : nan(""));
}

t_v3float
	calculate_plane_normal(float f, t_shape shape, t_ray ray)
{
	(void)f;
	if (v3f_dot(ray.direction, shape.shape_data.plane.normal) > 0)
		return (shape.shape_data.plane.normal);
	else
		return (v3f_multiply(shape.shape_data.plane.normal, -1));
}

float
	check_plane_collisons(t_shape shape, t_ray line)
{
	return (plane_intersecton(shape.shape_data.plane, line));
}
