/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:08:50 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/24 18:10:33 by lothieve         ###   ########.fr       */
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
	get_color(t_color color)
{
	int out;

	out = 0;
	out += color.r;
	out = out << 8;
	out += color.g;
	out = out << 8;
	out += color.b;
	return (out);
}
