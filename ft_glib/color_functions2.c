/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 12:06:13 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/13 14:10:23 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_color
	col_multiply(t_color color, double value)
{
	color.r *= value;
	color.g *= value;
	color.b *= value;
	return (color);
}

int
	median_color(int *levels, int size)
{
	t_color	*colors;
	t_color	out;
	int		i;
	int		med[3];

	colors = (t_color *)levels;
	i = -1;
	while (++i < 3)
		med[i] = 0;
	i = -1;
	while (++i < size)
	{
		med[0] += colors[i].r;
		med[1] += colors[i].g;
		med[2] += colors[i].b;
	}
	out.r = med[0] / size;
	out.g = med[1] / size;
	out.b = med[2] / size;
	return (get_color(out));
}

t_color
	new_color_i(int color)
{
	return (*(t_color *)&color);
}
