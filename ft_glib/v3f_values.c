/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:52:03 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/01 14:30:59 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_v3float new_v3f(float x, float y, float z)
{
	t_v3float out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

float v3f_magnitude(t_v3float v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_v3float v3f_normalize(t_v3float v)
{
	return v3f_divide_x(v, v3f_magnitude(v));
}

t_v3float to_v3f(t_vector3 v)
{
	return new_v3f(v.x, v.y, v.z);
}