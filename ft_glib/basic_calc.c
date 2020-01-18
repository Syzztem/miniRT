/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:43:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/13 12:39:07 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float
	square(float f)
{
	return (f * f);
}

unsigned char
	sat_add(unsigned char a, unsigned char b)
{
	return (a + b > 255 ? 255 : a + b);
}

float
	ft_fminpos(float a, float b)
{
	return (a < 0 ? a : b);
}
