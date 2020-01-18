/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:05:55 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/18 12:23:11 by lothieve         ###   ########.fr       */
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

void calculate_rotation_data(t_cam *cam)
{
	t_v3float unit;

	unit = new_v3f(0, 0, 1);
	cam->rot_data.r_cos = v3f_dot(unit, cam->rot);
	cam->rot_data.r_sin = sinf(acosf(cam->rot_data.r_cos));
	cam->rot_data.axe = v3f_normalize(v3f_multiply_v(unit, cam->rot));
}

t_alight get_alight(char *line)
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
