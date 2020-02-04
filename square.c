/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:48:39 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/04 13:31:58 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float
	check_square_collision(t_shape shape, t_ray line)
{
	float		d;
	t_v3float	op;

	if (!isnan(d = plane_intersecton(new_plane(shape.shape_data.square
		.orientation, shape.shape_data.square.pos), line)))
	{
		op = v3f_sub(ray_point_at(line, d),
			shape.shape_data.square.pos);
		if (v3f_magnitude(op) < shape.shape_data.square.side)
			return (d);
	}
	return (nan(""));
}

t_v3float
	calculate_square_normal(float f, t_shape shape, t_ray ray)
{
	(void)f;
	(void)ray;
	return (shape.shape_data.square.orientation);
}
