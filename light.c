/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:05:09 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/12 16:44:26 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int any_collision(t_ray ray, t_shape *shape_list, float max)
{
	float col_dist;

	while (shape_list)
	{
		col_dist = -shape_list->calculate_fun.collision(*shape_list, ray);
		printf("%f, %f\n", max, col_dist);
		if (!isnan(col_dist) && col_dist < max)
			return (1);
		shape_list = shape_list->next;
	}
	return (0);
}

int		lerp_light(t_light light, t_ray normal_ray, t_color albedo, t_shape *shape_list)
{
	t_ray	light_ray;
	float intensity;
	
	light_ray = ray_from_points(light.position, normal_ray.origin);
	if (any_collision(light_ray, shape_list, v3f_magnitude(v3f_substract_v(light.position, normal_ray.origin))))
		intensity = 0.2f;
	else
		intensity = fmax(v3f_dot(normal_ray.direction, light_ray.direction), 0) * light.intensity + 0.2f;
	if (intensity > 1)
		intensity = 1.0f;
	return (get_color(col_multiply(albedo, intensity)));
}

t_light	new_light(t_v3float position, float intensity, t_color color)
{
	return ((t_light) {.position = position, .intensity = intensity, .color = color});
}