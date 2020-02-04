/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:43:24 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/04 15:49:01 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float
	ft_fminpos(float a, float b)
{
	float lambda;

	if (a < -EPSILON)
	{
		if (b < -EPSILON)
			return (nan(""));
		else
			lambda = b;
	}
	else if (b < -EPSILON)
		lambda = a;
	else if (a < b)
		lambda = a;
	else 
		lambda = b;
	return (lambda);
}

float
	check_sphere_collisions(t_shape shape, t_ray line)
{
	t_v3float	oc;
	float		b;
	float		c;

	oc = v3f_sub(line.origin, shape.shape_data.sphere.center);
	b = v3f_dot(oc, line.direction);
	c = v3f_dot(oc, oc) - square(shape.shape_data.sphere.radius);
	c = sqrtf(square(b) - c);
	return (ft_fminpos(-b - c, c - b));
}

int
	sp_hit_or_miss(t_shape shape, t_ray line)
{
	t_v3float oc;

	oc = v3f_sub(line.origin, shape.shape_data.sphere.center);
	return (square(v3f_dot(oc, line.direction)) - v3f_dot(oc, oc) >= 0 ? 1 : 0);
}

t_v3float
	calculate_sphere_normal(float t, t_shape shape, t_ray ray)
{
	return (v3f_normalize(v3f_sub(ray_point_at(ray, t),
		shape.shape_data.sphere.center)));
}
