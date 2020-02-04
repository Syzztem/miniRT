/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 14:35:48 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/02 16:23:09 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	db_print_vector(t_v3float v)
{
	printf("%.2f, %.2f, %.2f\n", v.x, v.y, v.z);
}

void	db_print_color(t_color c)
{
	printf("r%d, g%d, b%d\n", c.r, c.g, c.b);
}
