/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:52:03 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/10 15:47:02 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_v3double
	new_v3f(double x, double y, double z)
{
	t_v3double out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

double
	v3f_square(t_v3double v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double
	v3f_magnitude(t_v3double v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_v3double
	v3f_normalize(t_v3double v)
{
	return (v3f_divide_x(v, v3f_magnitude(v)));
}

t_v3double
	to_v3f(t_vector3 v)
{
	return (new_v3f(v.x, v.y, v.z));
}
