/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:08:50 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/02 16:38:29 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_color
	new_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

int
	get_color_i(int r, int g, int b)
{
	int out;

	out = 0;
	out += r;
	out = out << 8;
	out += g;
	out = out << 8;
	out += b;
	return (out);
}

int
	get_color(t_color color)
{
	color.a = 0;
	return (*(int *)(&color));
}

t_color
	col_add(t_color a, t_color b)
{
	a.r = sat_add(a.r, b.r);
	a.g = sat_add(a.g, b.g);
	a.b = sat_add(a.b, b.b);
	return (a);
}

t_color
	col_multiply_c(t_color a, t_color b)
{
	a.r = a.r * b.r / 255;
	a.g = a.g * b.g / 255;
	a.b = a.b * b.b / 255;
	return (a);
}
