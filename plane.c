/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:36:59 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/08 12:29:50 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float
	plane_intersecton (t_plane plane, t_ray line)
{
	float d;

	d = v3f_dot(line.direction, plane.normal);
	if ( d == 0)
		return (sqrtf(-1));
	d = v3f_dot(v3f_substract_v(plane.p, line.origin), plane.normal) / d;
	return (d < VIEW_DISTANCE && d > 0 ? d : sqrtf(-1));
}

// TODO: return right vector direction depending on the side of the plan hit by the ray
t_v3float
	calculate_plane_normal(float f, t_shape shape, t_ray ray)
{
	(void) ray;
	(void) f;
	return (v3f_multiply_x(shape.shape_data.plane.normal, 0 ? 1 : -1));
}

float
	check_plane_collisons (t_shape shape, t_ray line)
{
	return (plane_intersecton (shape.shape_data.plane, line));
}

/*
float
	check_triangle_collisions (t_shape shape, t_ray line)
{
	float d;

	d = plane_intersecton(shape.shape_data.triangle.plane, line);
	if (!isnanf(d) && is_in_triangle(ray_point_at(line, d), shape.shape_data.triangle))
		return (d);
	else
		return (sqrtf(-1));
	
}
*/