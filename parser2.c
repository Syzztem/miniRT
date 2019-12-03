/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:20:17 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/27 10:09:24 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector3 get_v3(char **str)
{
	t_vector3 out;

	out.x = ft_atoi(*str);
	(*str) += ft_strilen(*str);
	if (**str == ',')
		(*str)++;
	out.y = ft_atoi(*str);
	(*str) += ft_strilen(*str);
	if (**str == ',')
		(*str)++;
	out.z = ft_atoi(*str);
	(*str) += ft_strilen(*str);
	while (ft_isspace(**str))
		(*str)++;
	return (out);
}

t_v3float get_v3f(char **str)
{
	t_v3float out;

	out.x = ft_atof(*str);
	(*str) += ft_strilen(*str);
	if (**str == '.')
		(*str)++;
	(*str) += ft_strilen(*str);
	if (**str == ',')
		(*str)++;
	out.y = ft_atof(*str);
	(*str) += ft_strilen(*str);
	if (**str == '.')
		(*str)++;
	*str += ft_strilen(*str);
	if (**str == ',')
		(*str)++;
	out.z = ft_atof(*str);
	(*str) += ft_strilen(*str);
	if (**str == '.')
		(*str)++;
	*str += ft_strilen(*str);
	return (out);
}