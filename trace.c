/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:03:00 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/02 15:31:51 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sdist
	tmin(t_shape *shape_list, t_ray ray)
{
	t_sdist	sdist;
	float	t;

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
	t_v3float	normal;
	t_sdist		closest_shape;
	float		t;

	closest_shape = tmin(scene.shape_list, ray);
	if (closest_shape.distance != 0)
	{
		normal = closest_shape.shape.calculate_normal(
			closest_shape.distance, closest_shape.shape, ray);
		if (v3f_dot(ray.direction, normal) > 0)
			normal = v3f_multiply_x(normal, -1);
		return (lerp_light(scene.light_list, new_ray(ray_point_at(ray,
			closest_shape.distance), normal), closest_shape.shape, scene,
			closest_shape.distance));
	}
	t = 1 - (ray.direction.y + 1) * 0.5f;
	return (0);
}

void
	image_pixel_put(t_image image, int x, int y, int color)
{
	image.img_data[x + y * image.size_line / sizeof(int)] = color;
}

t_image
	trace(t_scene scene, t_image image)
{
	int		i;
	int		j;
	float	dist_to_screen;
	t_ray	r;

	dist_to_screen = scene.resolution.x /
		(2 * tanf(DEG_TO_RAD * scene.camera->fov / 2));
	i = 0;
	while (i < scene.resolution.x)
	{
		j = 0;
		while (j < scene.resolution.y)
		{
			r = ray_from_points(scene.camera->pos,
				new_v3f(-i + scene.resolution.x / 2,
				j - scene.resolution.y / 2, -dist_to_screen));
			r.direction = v3f_rotate(r.direction, scene.camera->rot_data.axe,
				scene.camera->rot_data.r_sin, scene.camera->rot_data.r_cos);
			image_pixel_put(image, i, j, calculate_color(r, scene));
			j++;
		}
		i++;
	}
	scene.camera->render = image;
	return (image);
}

void
	next_view(t_scene *scene)
{
	scene->camera = scene->camera->next;
	if (!scene->camera->render.img_data)
	{
		scene->camera->render =
			generate_image(scene->resolution, scene->mlx_pointer);
		trace(*scene, scene->camera->render);
	}
	mlx_put_image_to_window(scene->mlx_pointer,
		scene->window_pointer, scene->camera->render.img_ptr, 0, 0);
}
