/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:44:13 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/10 15:48:38 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_ray
	new_ray(t_v3double origin, t_v3double direction)
{
	t_ray ray;

	ray.origin = origin;
	ray.direction = v3f_normalize(direction);
	return (ray);
}

t_sphere
	new_sphere(t_v3double center, double radius)
{
	t_sphere sphere;

	sphere.center = center;
	sphere.radius = radius;
	return (sphere);
}

t_plane
	new_plane(t_v3double normal, t_v3double p)
{
	t_plane plane;

	plane.normal = normal;
	plane.p = p;
	return (plane);
}

t_v3double
	ray_point_at(t_ray ray, double t)
{
	return (v3f_add(ray.origin, v3f_multiply(ray.direction, t)));
}

t_ray
	ray_from_points(t_v3double a, t_v3double b)
{
	return (new_ray(a, v3f_sub(a, b)));
}
