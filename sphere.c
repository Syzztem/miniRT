/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:43:24 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/10 15:40:26 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double
	check_sphere_collisions(t_shape shape, t_ray line)
{
	t_v3double	oc;
	double		b;
	double		c;

	oc = v3f_sub(line.origin, shape.shape_data.sphere.center);
	b = v3f_dot(oc, line.direction);
	c = v3f_dot(oc, oc) - square(shape.shape_data.sphere.radius);
	c = sqrtf(square(b) - c);
	return (ft_fminpos(-b - c, c - b));
}

t_v3double
	calculate_sphere_normal(double t, t_shape shape, t_ray ray)
{
	return (v3f_normalize(v3f_sub(ray_point_at(ray, t),
		shape.shape_data.sphere.center)));
}
