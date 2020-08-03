/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:43:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/02 16:59:45 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

double
	ft_fminpos(double a, double b)
{
	double lambda;

	if (isnan(a))
		return (b);
	if (isnan(b))
		return (a);
	if (a < EPSILON)
	{
		if (b < EPSILON)
			return (nan(""));
		else
			lambda = b;
	}
	else if (b < EPSILON)
		lambda = a;
	else if (a < b)
		lambda = a;
	else
		lambda = b;
	return (lambda);
}

double
	solve_quadra(double a, double b, double c)
{
	double delta;

	delta = sqrtf(b * b - 4 * a * c);
	if (isnan(delta))
		return (delta);
	b /= 2 * a;
	return (ft_fminpos(-b - delta, delta - b));
}

double
	square(double f)
{
	return (f * f);
}

unsigned char
	sat_add(unsigned char a, unsigned char b)
{
	return (a + b > 255 ? 255 : a + b);
}

size_t
	ft_strlen(const char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

float
	randfloat()
{
	return ((float)rand() / (float)(RAND_MAX)) * 2 - 1;
}