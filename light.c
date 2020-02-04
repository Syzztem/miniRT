/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:05:09 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/04 16:14:45 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int
	any_collision(t_ray ray, t_shape *shape_list, float distance)
{
	float col_dist;

	while (shape_list)
	{
		col_dist = -shape_list->calculate_fun.collision(*shape_list, ray);
		if (!isnan(col_dist) && col_dist < distance - 0.01f && col_dist > EPSILON)
			return (1);
		shape_list = shape_list->next;
	}
	return (0);
}

int
	lerp_light(t_ray normal_ray, t_shape shape, t_scene scene)
{
	t_ray	light_ray;
	float	multiplier;
	t_color	color;
	t_light *light;

	light = scene.light_list;
	color = new_color(0, 0, 0);
	while (light)
	{
		light_ray = ray_from_points(light->position, normal_ray.origin);
		color = col_add(col_multiply_c(shape.albedo,
			col_multiply(scene.ambient_light.color,
			scene.ambient_light.intensity)), color);
		if (!any_collision(light_ray, scene.shape_list, v3f_magnitude(v3f_sub(light->position, normal_ray.origin))))
		{
			multiplier = light->intensity *
				fmax(v3f_dot(normal_ray.direction, light_ray.direction), 0);
			color = col_add(col_multiply_c(shape.albedo,
				col_multiply(light->color, multiplier)), color);
		}
		light = light->next;
	}
	return (get_color(color));
}

t_light
	new_light(t_v3float position, float intensity, t_color color)
{
	return ((t_light) {.position = position,
		.intensity = intensity, .color = color});
}
