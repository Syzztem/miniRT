/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:43:24 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/10 16:45:56 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float
	check_sphere_collisions(t_shape shape, t_ray line)
{
	t_v3float oc = v3f_substract_v(line.origin, shape.shape_data.sphere.center);
	float b = v3f_dot(oc, line.direction);
	float c = v3f_dot(oc, oc);
	c -= square(shape.shape_data.sphere.radius);
	return(-b -sqrt(square(b) - c));
}
/*
float
	check_sphere_collisions(t_shape shape, t_ray line)
{
	float delta;
	float t0;
	float t;
	t_v3float p;

	p = v3f_substract_v(line.origin, shape.shape_data.sphere.center);
	delta = square(v3f_dot(line.direction, p))
		- square(v3f_magnitude(p)) + square(shape.shape_data.sphere.radius);
	if (delta < 0)
		return (sqrtf(-1));
	t0 = - v3f_dot(line.direction, p);
	t = t0 - sqrtf(delta);
//	if (v3f_multiply_x(line.direction, t).x > line.direction.x)
//		t = t0 + sqrtf(delta);
	return (t);
}
*/
t_v3float
	calculate_sphere_normal(float t, t_shape shape, t_ray ray)
{
	return (v3f_normalize(v3f_substract_v(ray_point_at(ray, t), shape.shape_data.sphere.center)));
}