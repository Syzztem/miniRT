/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:14:13 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/13 16:18:32 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int k_hook(int keycode, void *param)
{
	t_scene *scene;

	scene = (t_scene*)param;
	(void) param;
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(scene->mlx_pointer, scene->window_pointer);
		exit(0);
	}
	else if(keycode == 49)
		next_view(scene);
	return (0);
}