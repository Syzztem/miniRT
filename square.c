/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:48:39 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/10 15:53:54 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double
	check_square_collision(t_shape shape, t_ray line)
{
	double		d;
	t_v3double	op;

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

t_v3double
	calculate_square_normal(double f, t_shape shape, t_ray ray)
{
	(void)f;
	(void)ray;
	return (shape.shape_data.square.orientation);
}
