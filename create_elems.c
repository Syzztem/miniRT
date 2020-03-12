/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elems.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:38:48 by lothieve          #+#    #+#             */
/*   Updated: 2020/03/12 16:14:15 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

t_cylinder
	complete_cylinder(t_cylinder cy)
{
	t_ray cyr;

	cyr = new_ray(cy.pos, cy.orientation);
	cy.capa = ray_point_at(cyr, cy.height);
	cy.capb = ray_point_at(cyr, -cy.height);
	cy.normal = malloc(sizeof(t_v3double));
	cy.ca = v3f_sub(cy.capb, cy.capa);
	cy.caca = v3f_dot(cy.ca, cy.ca);
	return (cy);
}

t_shape
	*get_cylinder(char *line)
{
	t_shape *out;

	line += 2;
	line += skip_spaces(line);
	out = malloc(sizeof(t_shape));
	out->shape_data.cylinder.pos = get_v3f(&line);
	line += skip_spaces(line);
	out->shape_data.cylinder.orientation = v3f_normalize(get_v3f(&line));
	line += skip_spaces(line);
	out->shape_data.cylinder.radius = ft_atof(line) / 2.0f;
	line += flen(line);
	line += skip_spaces(line);
	out->shape_data.cylinder.height = ft_atof(line) / 2.0f;
	line += flen(line);
	line += skip_spaces(line);
	out->albedo = ft_atoc(line);
	out->calculate_fun.collision = check_cylinder_collision;
	out->calculate_normal = calculate_cylinder_normal;
	out->type = CYLINDER;
	out->shape_data.cylinder = complete_cylinder(out->shape_data.cylinder);
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
