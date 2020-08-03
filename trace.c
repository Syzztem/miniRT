/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:03:00 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/03 16:08:13 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sdist
	tmin(t_shape *shape_list, t_ray ray)
{
	t_sdist	sdist;
	double	t;

	sdist.distance = 0;
	while (shape_list)
	{
		t = shape_list->calculate_fun.collision(*shape_list, ray);
		if ((sdist.distance == 0 || sdist.distance > t)
			&& !isnan(t) && t > EPSILON)
			sdist = (t_sdist) {.shape = *shape_list, .distance = t};
		shape_list = shape_list->next;
	}
	return (sdist);
}

int
	calculate_color(t_ray ray, t_scene scene)
{
	t_sdist		closest_shape;

	closest_shape = tmin(scene.shape_list, ray);
	if (closest_shape.distance == 0)
		return (0);
	return (blend_light(closest_shape, scene, ray));
}

#ifdef AALVL

#include <stdio.h>
static int
	shoot_ray(t_scene scene, int i, int j, int dist_to_screen)
{
	t_ray r;
	int aa;
	float randx;
	float randy;
	int levels[AALVL];

	aa = -1;
	while (++aa < AALVL)
	{
		randx = randfloat();
		randy = randfloat();
		r = ray_from_points(scene.camera->pos,
			new_v3f(-i + scene.resolution.x / 2 + randx / 2,
			j - scene.resolution.y / 2 + randy / 2, -dist_to_screen));
		r.direction = v3f_rotate(r.direction, scene.camera->rot_data.axe,
			scene.camera->rot_data.r_sin, scene.camera->rot_data.r_cos);
		levels[aa] = calculate_color(r, scene);
	}
	return (median_color(levels, AALVL));
}

#else

static int
	shoot_ray(t_scene scene, int i, int j, int dist_to_screen)
{
	t_ray r;

	r = ray_from_points(scene.camera->pos,
		new_v3f(-i + scene.resolution.x / 2,
		j - scene.resolution.y / 2, -dist_to_screen));
	r.direction = v3f_rotate(r.direction, scene.camera->rot_data.axe,
		scene.camera->rot_data.r_sin, scene.camera->rot_data.r_cos);
	return (calculate_color(r, scene));
}

#endif

t_image
	trace(t_scene scene, t_image image)
{
	int		i;
	int		j;
	double	dist_to_screen;

	dist_to_screen = scene.resolution.x /
		(2 * tanf(DEG_TO_RAD * scene.camera->fov / 2));
	i = 0;
	while (i < scene.resolution.x)
	{
		j = 0;
		while (j < scene.resolution.y)
		{
			image_pixel_put(image, i, j,
				shoot_ray(scene, i, j, dist_to_screen));
			j++;
		}
		i++;
	}
	scene.camera->render = image;
	return (image);
}
