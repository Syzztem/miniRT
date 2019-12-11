/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:05:09 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/11 13:54:25 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	lerp_light(t_light light, t_v3float normal, t_v3float hitpoint)
{
	t_ray light_ray;

	light_ray = ray_from_points(light.position, hitpoint);
	return (1 - fabsf(v3f_dot(light_ray.direction, normal)));
}

t_light	new_light(t_v3float position, float intensity, t_color color)
{
	return ((t_light) {.position = position, .intensity = intensity, .color = color});
}