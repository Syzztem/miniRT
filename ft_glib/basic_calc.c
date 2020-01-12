/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:43:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/11 11:48:55 by lothieve         ###   ########.fr       */
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
