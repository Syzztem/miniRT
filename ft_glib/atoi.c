/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:08:46 by lothieve          #+#    #+#             */
/*   Updated: 2020/10/21 11:23:08 by lothieve         ###   ########.fr       */
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
	int		i;
	double	res;
	char	sign;
	double	pos;

	pos = 0.1;
	res = 0;
	sign = 1;
	i = -1;
	while (ft_isspace(*str))
		str++;
	while (str[++i] == '+' || str[i] == '-')
		if (str[i] == '-')
			sign = -sign;
	i--;
	while (str[++i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i] - 48;
	if (str[i] == '.')
		while (str[++i] >= '0' && str[i] <= '9')
		{
			res += pos * (str[i] - 48);
			pos *= 0.1;
		}
	return (res * sign);
}
