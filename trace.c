/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:03:00 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/14 14:08:11 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

#ifdef AALVL

static int
	shoot_ray(t_scene scene, int i, int j, int dist_to_screen)
{
	t_ray	r;
	int		aa;
	float	randx;
	float	randy;
	int		levels[AALVL];

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

#ifdef THREADX

void
	*run_thread(void *param)
{
	t_thread_food	*food;
	int				i;
	int				j;
	double			dist_to_screen;

	food = param;
	i = food->tl.x;
	dist_to_screen = food->scene.resolution.x /
		(2 * tanf(DEG_TO_RAD * food->scene.camera->fov / 2));
	while (i < food->br.x)
	{
		j = food->tl.y;
		while (j < food->br.y)
		{
			image_pixel_put(food->image, i, j,
				shoot_ray(food->scene, i, j, dist_to_screen));
			j++;
		}
		i++;
	}
	free(param);
	return (NULL);
}

t_image
	*trace(t_scene scene, t_image *image)
{
	pthread_t		*threads;
	unsigned int	i;
	unsigned int	count;
	t_thread_food	*param;
	t_vector2		size;

	count = THREADX * THREADY;
	threads = malloc(sizeof(pthread_t) * count);
	size.x = scene.resolution.x / THREADX;
	size.y = scene.resolution.y / THREADY;
	i = -1;
	while (++i < count && (param = malloc(sizeof(t_thread_food))))
	{
		*param = (t_thread_food) {.image = image, .scene = scene,
		.tl = (t_vector2) {.x = size.x * (i % THREADX), .y = param->tl.y =
		size.y * (i / THREADX)}, .br = (t_vector2) {.x = size.x *
		(i % THREADX + 1), .y = size.y * (i / THREADX + 1)}};
		pthread_create(&threads[i], NULL, run_thread, param);
	}
	i = -1;
	while (++i < count)
		pthread_join(threads[i], NULL);
	free(threads);
	scene.camera->render = image;
	return (image);
}

#else

t_image
	*trace(t_scene scene, t_image *image)
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

#endif
