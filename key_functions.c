/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:14:13 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/04 14:08:53 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	k_hook(int keycode, void *param)
{
	t_scene *scene;

	scene = (t_scene*)param;
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		yeet(*scene, 0);
	}
	else if (keycode == 49)
		next_view(scene);
	else if (keycode == 1)
		create_bitmap(scene->camera->render, "render");
	return (0);
}

int	xyeet(void *param)
{
	yeet(*(t_scene *)param, 0);
	return (0);
}
