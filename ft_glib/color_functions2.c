/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 12:06:13 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/10 15:52:56 by lothieve         ###   ########.fr       */
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
