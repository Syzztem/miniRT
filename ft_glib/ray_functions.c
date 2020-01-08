/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:44:13 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/05 12:43:46 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_ray new_ray(t_v3float origin, t_v3float direction)
{
	t_ray ray;

	ray.origin = origin;
	ray.direction = v3f_normalize(direction);
	return (ray);
}

t_sphere new_sphere(t_v3float center, float radius)
{
	t_sphere sphere;

	sphere.center = center;
	sphere.radius = radius;
	return (sphere);
}

t_plane new_plane(t_v3float normal, t_v3float p)
{
	t_plane plane;

	plane.normal = normal;
	plane.p = p;
	return (plane);
}

t_v3float ray_point_at(t_ray ray, float t)
{
	return (v3f_add(ray.origin, v3f_multiply_x(ray.direction, t)));
}

t_ray	ray_from_points(t_v3float a, t_v3float b)
{
	return (new_ray(a, v3f_substract_v(a, b)));
}