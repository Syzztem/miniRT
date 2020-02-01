/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:36:59 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/21 16:28:01 by lothieve         ###   ########.fr       */
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
	d = v3f_dot(v3f_substract_v(plane.p, line.origin), plane.normal) / d;
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
		return (v3f_multiply_x(shape.shape_data.plane.normal, -1));
}

t_v3float
	calculate_triangle_normal(float f, t_shape shape, t_ray ray)
{
	(void)f;
	if (v3f_dot(ray.direction, shape.shape_data.triangle.normal) > 0)
		return (shape.shape_data.plane.normal);
	else
		return (v3f_multiply_x(shape.shape_data.triangle.normal, -1));
}

float
	check_plane_collisons(t_shape shape, t_ray line)
{
	return (plane_intersecton(shape.shape_data.plane, line));
}

int
	triangle_hit_or_miss(t_triangle tri, t_ray line)
{
	t_v3float	tvec;
	t_v3float	pvec;
	float		det;
	float		u;
	float		v;

	pvec = v3f_multiply_v(line.direction, tri.ac);
	det = v3f_dot(tri.ab, pvec);
	if (fabsf(det) < EPSILON)
		return (0);
	det = 1 / det;
	tvec = v3f_substract_v(line.origin, tri.vertices[0]);
	u = v3f_dot(tvec, pvec) * det;
	if (u < EPSILON || u > 1 - EPSILON)
		return (0);
	tvec = v3f_multiply_v(tvec, tri.ab);
	v = v3f_dot(tvec, line.direction) * det;
	if (v < EPSILON || u + v > 1 - EPSILON)
		return (0);
	return (1);
}

float
	check_triangle_collisons(t_shape shape, t_ray line)
{
	if (triangle_hit_or_miss(shape.shape_data.triangle, line))
		return (plane_intersecton((t_plane)
			{.normal = shape.shape_data.triangle.normal,
			.p = shape.shape_data.triangle.vertices[0]}, line));
	return (nan(""));
}
