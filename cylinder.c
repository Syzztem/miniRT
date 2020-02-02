/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:30:26 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/02 13:07:57 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float disk_collision(t_shape shape, t_ray line)
{
	float d;
	if (!isnan(d = plane_intersecton(new_plane(shape.shape_data.square.orientation,
		shape.shape_data.square.pos), line)))
	{
		t_v3float op = v3f_substract_v(ray_point_at(line, d), shape.shape_data.square.pos);
		if (v3f_magnitude(op) < shape.shape_data.square.side)
			return (d);
	}
	return (nan(""));
}

t_v3float
	calculate_cylinder_normal(float f, t_shape shape, t_ray ray)
{
	t_v3float hb;
	float scale;
	t_v3float out;

	hb = v3f_substract_v(ray_point_at(ray, f), shape.shape_data.cylinder.pos);
	scale = v3f_dot(hb, shape.shape_data.cylinder.oritentation);
	out = v3f_substract_v(hb, v3f_multiply_x(shape.shape_data.cylinder.oritentation, scale));
	return (v3f_normalize(out));
}

float check_cylinder_collision(t_shape shape, t_ray line)
{
	t_v3float rc;
	t_v3float n;
	t_v3float o;
	float nnorm;
	float t;
	float s;
	float d;
	float lambda;

	rc = v3f_substract_v(line.origin, shape.shape_data.cylinder.pos);
	n = v3f_cross(line.direction, shape.shape_data.cylinder.oritentation);
	nnorm = v3f_magnitude(n);
	if (nnorm < EPSILON && nnorm > -EPSILON)
		return (nan(""));
	n = v3f_divide_x(n, nnorm);
	if ((d = fabsf(v3f_dot(rc, n))) < shape.shape_data.cylinder.diameter)
	{
		o = v3f_cross(rc, shape.shape_data.cylinder.oritentation);
		t = v3f_dot(o, n) / nnorm;
		o = v3f_cross(n, shape.shape_data.cylinder.oritentation);
		o = v3f_normalize(o);
		s  = fabsf(sqrtf(square(shape.shape_data.cylinder.diameter) - d * d) / v3f_dot(line.direction, o));
		float in = t - s;
		float out = t + s;
		if (in < -EPSILON)
		{
			if (out < -EPSILON)
				return (nan(""));
			else
				lambda = out;
		}
		else if (out < -EPSILON)
			lambda = in;
		else if (in < out)
			lambda = in;
		else lambda = out;
		return (lambda);
	}
	return (nan(""));
}