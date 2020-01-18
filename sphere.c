/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:43:24 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/16 10:23:08 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float
	check_sphere_collisions(t_shape shape, t_ray line)
{
	t_v3float	oc;
	float		b;
	float		c;

	oc = v3f_substract_v(line.origin, shape.shape_data.sphere.center);
	b = v3f_dot(oc, line.direction);
	c = v3f_dot(oc, oc) -square(shape.shape_data.sphere.radius);
	c = sqrtf(square(b) - c);
	return (-b - c);
	return (ft_fminpos(-b - c, c - b));
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
	if (shape.type == PLANE)
		return (calculate_plane_normal(t, shape, ray));
	return (v3f_normalize(v3f_substract_v(ray_point_at(ray, t), shape.shape_data.sphere.center)));
}
