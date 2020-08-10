/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:08:46 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/07 14:35:01 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

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
		out = out * 10 + *str - '0';
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
