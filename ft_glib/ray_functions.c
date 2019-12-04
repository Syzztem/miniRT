/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:44:13 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/04 14:08:45 by lothieve         ###   ########.fr       */
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

t_v3float ray_point_at(t_ray ray, float t)
{
	return (v3f_add(ray.origin, v3f_multiply_x(ray.direction, t)));
}