/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:20:17 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/17 16:55:28 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
