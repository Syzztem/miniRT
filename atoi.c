/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:08:46 by lothieve          #+#    #+#             */
/*   Updated: 2020/03/10 15:45:14 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int
	ft_strilen(const char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

static void
	addto(unsigned int *out, char c)
{
	*out *= 10;
	*out += c - '0';
}

int
	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	out;

	sign = 1;
	out = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		addto(&out, *str);
		str++;
	}
	return (out * sign);
}

double
	ft_atof(const char *str)
{
	int		integer_part;
	int		decimal_part;
	double	out;

	integer_part = ft_atoi(str);
	str += ft_strilen(str);
	if (*str == '.')
		str++;
	else
		return (integer_part);
	decimal_part = ft_atoi(str);
	if (integer_part == 0 && decimal_part == 0)
		return (0);
	out = (double)integer_part + (double)decimal_part / (ft_strilen(str) * 10);
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
