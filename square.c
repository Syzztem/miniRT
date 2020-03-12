/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:48:39 by lothieve          #+#    #+#             */
/*   Updated: 2020/03/12 16:29:58 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double
	check_square_collision(t_shape shape, t_ray line)
{
	double		d;
	t_v3double	op;
	t_square	sq;

	sq = shape.shape_data.square;
	if (isnan(d = plane_intersecton(new_plane(shape.shape_data.square
		.orientation, shape.shape_data.square.pos), line)))
		return (nan(""));
	op = ray_point_at(line, d);
	op = v3f_sub(op, sq.pos);
	sq.side = sq.side / 2 - 0.001;
	if (fabs(op.x) > sq.side || fabs(op.y) > sq.side || fabs(op.z) > sq.side)
		return (nan(""));
	return (d);
}

t_v3double
	calculate_square_normal(double f, t_shape shape, t_ray ray)
{
	(void)f;
	(void)ray;
	return (shape.shape_data.square.orientation);
}
