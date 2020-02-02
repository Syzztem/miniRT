/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:13:45 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/02 15:09:07 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void
	free_cam_list(t_cam *cam_list, void *mlx_ptr)
{
	t_cam *current;
	t_cam *next;

	if (!cam_list)
		return ;
	current = cam_list;
	next = current->next;
	current->next = NULL;
	current = next;
	while (current)
	{
		next = current->next;
		if (current->render.img_data)
			mlx_destroy_image(mlx_ptr, current->render.img_ptr);
		free(current);
		current = next;
	}
}

void
	free_shape_list(t_shape *shape_list)
{
	t_shape	*current;
	t_shape	*next;

	if (!shape_list)
		return ;
	current = shape_list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void
	free_light_list(t_light *light_list)
{
	t_light *current;
	t_light *next;

	if (!light_list)
		return ;
	current = light_list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void
	yeet(t_scene scene, int ret)
{
	free_cam_list(scene.camera, scene.mlx_pointer);
	free_shape_list(scene.shape_list);
	free_light_list(scene.light_list);
	mlx_destroy_window(scene.mlx_pointer, scene.window_pointer);
	exit(ret);
}