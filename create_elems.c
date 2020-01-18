/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elems.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:38:48 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/18 17:11:56 by lothieve         ###   ########.fr       */
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
	elem->rot = get_v3f(&line);
	elem->fov = ft_atoi(line);
	calculate_rotation_data(elem);
	elem->next = NULL;
	return (elem);
}

t_shape
	*get_sphere(char *line)
{
	t_shape *out;

	out = malloc(sizeof(t_shape));
	line += 2;
	while (ft_isspace(*line))
		line++;
	puts(line);
	out->shape_data.sphere.center = get_v3f(&line);
	while (ft_isspace(*line))
		line++;
	out->shape_data.sphere.radius = ft_atof(line);
	while (ft_isspace(*line))
		line++;
	out->albedo = ft_atoc(line);
	out->calculate_fun.collision = check_sphere_collisions;
	out->calculate_normal = calculate_sphere_normal;
	out->next = NULL;
	out->type = SPHERE;
	return (out);
}

t_light
	*get_light(char *line)
{
	t_light *out;

	line++;
	out = malloc(sizeof(t_light));
	while (ft_isspace(*line))
		line++;
	out->position = get_v3f(&line);
	while (ft_isspace(*line))
		line++;
	out->intensity = ft_atof(line);
	(line) += ft_strilen(line);
	if (*line == '.')
		line++;
	line += ft_strilen(line);
	while (ft_isspace(*line))
		line++;
	out->color = ft_atoc(line);
	out->next = NULL;
	return (out);
}

void
	add_sphere(char *line, t_shape **shape_list)
{
	t_shape *elem;

	elem = *shape_list;
	if (!elem)
		*shape_list = get_sphere(line);
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = get_sphere(line);
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
	add_light(char *line, t_light **light_list)
{
	t_light *elem;

	elem = *light_list;
	if (!elem)
		*light_list = get_light(line);
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = get_light(line);
	}
}