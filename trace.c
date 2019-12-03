/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:43:24 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/02 20:21:38 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float
	check_sphere_collisions(t_line line, t_sphere sphere)
{
	float delta;
	float t0;
	float t;
	t_v3float p;

	p = v3f_substract_v(line.origin, sphere.center);
	delta = square(v3f_dot(line.direction, p))
		- (square(v3f_magnitude(p)) - square(sphere.radius));
	if (delta < 0)
		return(sqrtf(-1));
	printf("%.2f, %.2f\n", line.direction.x, line.direction.y);
	t0 = - v3f_dot(line.direction, p);
	t = t0 - sqrtf(delta);
	if (v3f_multiply_x(line.direction, t).x > line.direction.x)
		t = t0 + sqrtf(delta);
	return t;
}