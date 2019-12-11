/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:43:24 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/11 11:19:37 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float
	check_sphere_collisions(t_shape shape, t_ray line)
{
	t_v3float oc;

	oc = v3f_substract_v(line.origin, shape.shape_data.sphere.center);
	float b = v3f_dot(oc, line.direction);
	float c = v3f_dot(oc, oc);
	c -= square(shape.shape_data.sphere.radius);
	return(-b -sqrt(square(b) - c));
}

int
	sp_hit_or_miss(t_shape shape, t_ray line)
{
	t_v3float oc;

	oc = v3f_substract_v(line.origin, shape.shape_data.sphere.center);
	return (square(v3f_dot(oc, line.direction)) - v3f_dot(oc, oc) >= 0 ? 1 : 0);
}

t_v3float
	calculate_sphere_normal(float t, t_shape shape, t_ray ray)
{
	return (v3f_normalize(v3f_substract_v(ray_point_at(ray, t), shape.shape_data.sphere.center)));
}