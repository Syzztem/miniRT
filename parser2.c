/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:20:17 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/13 14:32:20 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int
	skip_spaces(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

t_v3double
	get_v3f(char **str)
{
	t_v3double out;

	out.x = ft_atof(*str);
	(*str) += flen(*str);
	if (**str == ',')
		(*str)++;
	else
		g_error = 1;
	out.y = ft_atof(*str);
	(*str) += flen(*str);
	if (**str == ',')
		(*str)++;
	else
		g_error = 1;
	out.z = ft_atof(*str);
	(*str) += flen(*str);
	return (out);
}

t_color
	ft_atoc(const char *str)
{
	t_color out;

	out.r = ft_atoi(str);
	if ((int)out.r != ft_atoi(str))
		g_error = 1;
	str += ft_strilen(str);
	if (*str == ',')
		str++;
	else
		g_error = 1;
	out.g = ft_atoi(str);
	if ((int)out.g != ft_atoi(str))
		g_error = 1;
	str += ft_strilen(str);
	if (*str == ',')
		str++;
	else
		g_error = 1;
	out.b = ft_atoi(str);
	if ((int)out.b != ft_atoi(str))
		g_error = 1;
	str += ft_strilen(str);
	return (out);
}
