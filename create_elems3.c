/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elems3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:57:36 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/03 16:27:43 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_light
	*get_light(char *line)
{
	t_light *out;

	line++;
	while (ft_isspace(*line))
		line++;
	out = malloc(sizeof(t_light));
	out->position = get_v3f(&line);
	while (ft_isspace(*line))
		line++;
	out->intensity = ft_atof(line);
	line += flen(line);
	while (ft_isspace(*line))
		line++;
	out->color = ft_atoc(line);
	out->next = NULL;
	return (out);
}

t_shape
	*get_sphere(char *line)
{
	t_shape *out;

	out = malloc(sizeof(t_shape));
	line += 2;
	while (ft_isspace(*line))
		line++;
	out->shape_data.sphere.center = get_v3f(&line);
	while (ft_isspace(*line))
		line++;
	out->shape_data.sphere.radius = ft_atof(line) / 2.0f;
	line += flen(line);
	out->albedo = ft_atoc(line);
	out->calculate_fun.collision = check_sphere_collisions;
	out->calculate_normal = calculate_sphere_normal;
	out->next = NULL;
	out->type = SPHERE;
	return (out);
}

t_shape
	*get_triangle(char *line)
{
	t_shape	*out;
	int		i;

	line += 2;
	line += skip_spaces(line);
	out = malloc(sizeof(t_shape));
	i = -1;
	while (++i < 3)
	{
		out->shape_data.triangle.vertices[i] = get_v3f(&line);
		line += skip_spaces(line);
	}
	out->shape_data.triangle.ab = v3f_sub(out->shape_data.triangle.
		vertices[1], out->shape_data.triangle.vertices[0]);
	out->shape_data.triangle.ac = v3f_sub(out->shape_data.triangle.
		vertices[2], out->shape_data.triangle.vertices[0]);
	out->shape_data.triangle.normal = v3f_normalize(v3f_cross(
		out->shape_data.triangle.ab, out->shape_data.triangle.ac));
	out->calculate_fun.collision = check_triangle_collisons;
	out->calculate_normal = calculate_triangle_normal;
	out->albedo = ft_atoc(line);
	out->next = NULL;
	out->type = TRIANGLE;
	return (out);
}

void
	add_triangle(char *line, t_shape **shape_list)
{
	t_shape *elem;

	elem = *shape_list;
	if (!elem)
		*shape_list = get_triangle(line);
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = get_triangle(line);
	}
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
