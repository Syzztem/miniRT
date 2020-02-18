/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:05:55 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/17 16:39:05 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int
	ft_isspace(int c)
{
	if (c == '\t'
			|| c == '\n'
			|| c == '\v'
			|| c == '\f'
			|| c == '\r'
			|| c == ' ')
		return (1);
	return (0);
}

t_vector2
	get_res(char *line)
{
	t_vector2 out;

	line++;
	while (ft_isspace(*line))
		line++;
	out.x = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line != ' ')
		g_error = 1;
	out.y = ft_atoi(line);
	return (out);
}

void
	calculate_rotation_data(t_cam *cam)
{
	t_v3double unit;

	unit = new_v3f(0, 0, 1);
	if (cam->rot.x == 0 && cam->rot.y == 0 && cam->rot.z == -1)
		cam->rot_data.r_cos = 10;
	else
		cam->rot_data.r_cos = v3f_dot(unit, cam->rot);
	cam->rot_data.r_sin = sinf(acosf(cam->rot_data.r_cos));
	cam->rot_data.axe = v3f_normalize(v3f_cross(unit, cam->rot));
}

int
	flen(char *str)
{
	int i;

	i = ft_strilen(str);
	if (str[i] == '.')
	{
		i++;
		i += ft_strilen(str);
	}
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

t_alight
	get_alight(char *line)
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
