/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:05:09 by lothieve          #+#    #+#             */
/*   Updated: 2020/03/11 17:11:08 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int
	any_hit(t_ray light_ray, t_shape *shapes, double distance, t_sdist surface)
{
	double dist;

	(void)surface;
	while (shapes)
	{
		dist = shapes->calculate_fun.collision(*shapes, light_ray);
		if (!isnan(dist) && dist > 0.01f && dist < distance - 0.01f)
		{
			return (1);
		}
		shapes = shapes->next;
	}
	return (0);
}

int
	blend_light(t_sdist surface, t_scene scene, t_ray cam_ray)
{
	t_v3double	normal;
	t_v3double	hit_position;
	t_color		color;
	t_ray		light_ray;
	t_v3double	v;

	hit_position = ray_point_at(cam_ray, surface.distance);
	color = col_multiply_c(surface.shape.albedo,
		col_multiply(scene.ambient_light.color, scene.ambient_light.intensity));
	normal = surface.shape.calculate_normal(surface.distance,
		surface.shape, cam_ray);
	while (scene.light_list)
	{
		v = v3f_sub(hit_position, scene.light_list->position);
		light_ray = new_ray(scene.light_list->position, v);
		if (!any_hit(light_ray, scene.shape_list, v3f_magnitude(v), surface))
			color = col_add(col_multiply_c(surface.shape.albedo,
				col_multiply(scene.light_list->color, fabs(v3f_dot(normal,
				light_ray.direction)) * scene.light_list->intensity)),
				color);
		scene.light_list = scene.light_list->next;
	}
	return (get_color(color));
}

t_light
	new_light(t_v3double position, double intensity, t_color color)
{
	return ((t_light) {.position = position,
		.intensity = intensity, .color = color});
}
