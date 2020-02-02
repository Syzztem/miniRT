/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elems.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:38:48 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/02 16:00:31 by lothieve         ###   ########.fr       */
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
	*get_square(char *line)
{
	t_shape *out;

	line += 2;
	while (ft_isspace(*line))
		line++;
	out = malloc(sizeof(t_shape));
	out->shape_data.square.pos = get_v3f(&line);
	while (ft_isspace(*line))
		line++;
	out->shape_data.square.orientation = v3f_normalize(get_v3f(&line));
	while (ft_isspace(*line))
		line++;
	out->shape_data.square.side = ft_atof(line);
	line += flen(line);
	while (ft_isspace(*line))
		line++;
	out->albedo = ft_atoc(line);
	out->calculate_fun.collision = check_square_collision;
	out->calculate_normal = calculate_square_normal;
	out->type = SQUARE;
	return (out);
}

t_shape
	*get_cylinder(char *line)
{
	t_shape *out;

	line += 2;
	while (ft_isspace(*line))
		line++;
	out = malloc(sizeof(t_shape));
	out->shape_data.cylinder.pos = get_v3f(&line);
	while (ft_isspace(*line))
		line++;
	out->shape_data.cylinder.oritentation = v3f_normalize(get_v3f(&line));
	while (ft_isspace(*line))
		line++;
	out->shape_data.cylinder.diameter = ft_atof(line);
	line += flen(line);
	while (ft_isspace(*line))
		line++;
	out->shape_data.cylinder.height = ft_atof(line);
	line += flen(line);
	while (ft_isspace(*line))
		line++;
	out->albedo = ft_atoc(line);
	out->calculate_fun.collision = check_cylinder_collision;
	out->calculate_normal = calculate_cylinder_normal;
	out->type = CYLINDER;
	return (out);
}

void
	add_square(char *line, t_shape **shape_list)
{
	t_shape *elem;

	elem = *shape_list;
	if (!elem)
		*shape_list = get_square(line);
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = get_square(line);
	}
}

void
	add_cylinder(char *line, t_shape **shape_list)
{
	t_shape *elem;

	elem = *shape_list;
	if (!elem)
		*shape_list = get_cylinder(line);
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = get_cylinder(line);
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
