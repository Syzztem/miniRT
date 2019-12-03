/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:05:55 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/27 20:40:27 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector2 get_res(char *line)
{
	t_vector2 out;

	line++;
	while (ft_isspace(*line))
		line++;
	out.x = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	out.y = ft_atoi(line);
	return(out);
}

t_alight get_light(char *line)
{
	t_alight out;

	line++;
	while (ft_isspace(*line))
		line++;
	out.intensity = ft_atof(line);
	while ((*line >= '0' && *line <= '9'))
		line++;
	if (*line == '.')
		line++;
	while ((*line >= '0' && *line <= '9'))
		line++;
	while (ft_isspace(*line))
		line++;
	out.color = ft_atoc(line);
	return (out);
}

t_cam mom_get_camera(char *line)
{
	t_cam out;

	line++;
	while (ft_isspace(*line))
		line++;
	out.pos = get_v3(&line);
	out.rot = get_v3f(&line);
	out.fov = ft_atoi(line);
	return (out);
}
/*
t_sphere get_sphere(char *line)
{
	t_sphere sphere;
	(void) line;
	return (sphere);
}
*/