/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elems2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:56:50 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/02 15:59:03 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_shape
	*get_plane(char *line)
{
	t_shape *out;

	out = malloc(sizeof(t_shape));
	line += 2;
	while (ft_isspace(*line))
		line++;
	out->shape_data.plane.p = get_v3f(&line);
	while (ft_isspace(*line))
		line++;
	out->shape_data.plane.normal = get_v3f(&line);
	out->albedo = ft_atoc(line);
	out->calculate_fun.collision = check_plane_collisons;
	out->calculate_normal = calculate_plane_normal;
	out->type = PLANE;
	out->next = NULL;
	return (out);
}

t_cam
	*create_cam(char *line)
{
	t_cam *elem;

	elem = malloc(sizeof(t_cam));
	line++;
	while (ft_isspace(*line))
		line++;
	elem->pos = get_v3f(&line);
	while (ft_isspace(*line))
		line++;
	elem->rot = v3f_normalize(get_v3f(&line));
	elem->fov = ft_atoi(line);
	calculate_rotation_data(elem);
	elem->next = NULL;
	elem->render.img_data = NULL;
	return (elem);
}

void
	add_cam(char *line, t_cam **cam_list)
{
	t_cam *elem;

	elem = *cam_list;
	if (!elem)
		*cam_list = create_cam(line);
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = create_cam(line);
	}
}

void
	add_plane(char *line, t_shape **shape_list)
{
	t_shape *elem;

	elem = *shape_list;
	if (!elem)
		*shape_list = get_plane(line);
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = get_plane(line);
	}
}
