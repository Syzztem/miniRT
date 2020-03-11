/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:24:48 by lothieve          #+#    #+#             */
/*   Updated: 2020/03/10 17:36:31 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int
	triangle_hit_or_miss(t_triangle tri, t_ray line)
{
	t_v3double	tvec;
	t_v3double	pvec;
	double		det;
	double		u;
	double		v;

	pvec = v3f_cross(line.direction, tri.ac);
	det = v3f_dot(tri.ab, pvec);
	if (fabs(det) < EPSILON)
		return (0);
	det = 1 / det;
	tvec = v3f_sub(line.origin, tri.vertices[0]);
	u = v3f_dot(tvec, pvec) * det;
	if (u < EPSILON || u > 1 - EPSILON)
		return (0);
	tvec = v3f_cross(tvec, tri.ab);
	v = v3f_dot(tvec, line.direction) * det;
	if (v < EPSILON || u + v > 1 - EPSILON)
		return (0);
	return (1);
}

double
	check_triangle_collisons(t_shape shape, t_ray line)
{
	if (triangle_hit_or_miss(shape.shape_data.triangle, line))
		return (plane_intersecton((t_plane){
			.normal = shape.shape_data.triangle.normal,
			.p = shape.shape_data.triangle.vertices[0]}, line));
		return (nan(""));
}

t_v3double
	calculate_triangle_normal(double f, t_shape shape, t_ray ray)
{
	(void)f;
	if (v3f_dot(ray.direction, shape.shape_data.triangle.normal) > 0)
		return (shape.shape_data.triangle.normal);
	else
		return (v3f_multiply(shape.shape_data.triangle.normal, -1));
}
