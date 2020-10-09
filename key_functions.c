/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:14:13 by lothieve          #+#    #+#             */
/*   Updated: 2020/09/30 11:57:06 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#ifdef LINUX
#else
# define EXIT 53
# define NEXT 49
# define SAVE 1
# define BLWH 38
# define SEPI 40
# define INVT 37
# define REST 4
#endif
#include <stdio.h>

void
	next_view(t_scene *scene)
{
	scene->camera = scene->camera->next;
	if (!scene->camera->render)
	{
		scene->camera->render =
			generate_image(scene->resolution, scene->mlx_pointer);
		trace(*scene, scene->camera->render);
	}
	mlx_put_image_to_window(scene->mlx_pointer,
		scene->window_pointer, scene->camera->render->img_ptr, 0, 0);
}

void
	apply_filter(t_scene *scene, t_filter filter)
{
	t_image			*image;
	static t_image	*filtered;

	image = scene->camera->render;
	if (!filtered)
		filtered = generate_image(scene->resolution, scene->mlx_pointer);
	ft_memcpy(filtered->img_data, image->img_data,
		scene->resolution.x * scene->resolution.y * sizeof(int));
	if (filter)
		filter(filtered);
	mlx_put_image_to_window(scene->mlx_pointer,
		scene->window_pointer, filtered->img_ptr, 0, 0);
}

int	k_hook(int keycode, void *param)
{
	t_scene *scene;

	scene = (t_scene*)param;
	if (keycode == EXIT)
		yeet(*scene, 0, NULL);
	else if (keycode == NEXT)
		next_view(scene);
	else if (keycode == SAVE)
		create_bitmap(*scene->camera->render, "render");
	else if (keycode == BLWH)
		apply_filter(scene, filter_bw);
	else if (keycode == SEPI)
		apply_filter(scene, filter_sepia);
	else if (keycode == INVT)
		apply_filter(scene, filter_inv);
	else if (keycode == REST)
		apply_filter(scene, NULL);
	return (0);
}

int	xyeet(void *param)
{
	yeet(*(t_scene *)param, 0, NULL);
	return (0);
}
