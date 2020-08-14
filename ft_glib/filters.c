/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:35:08 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/13 14:14:43 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"

t_image	*filter_bw(t_image *image)
{
	size_t	i;
	size_t	total_size;
	t_color	*current_pixel;

	total_size = image->res.x * image->res.y;
	i = 0;
	while (i < total_size)
	{
		current_pixel = (t_color *)&image->img_data[i];
		current_pixel->r = (current_pixel->r
			+ current_pixel->g + current_pixel->b) / 3;
		current_pixel->g = current_pixel->r;
		current_pixel->b = current_pixel->r;
		i++;
	}
	return (image);
}

t_image	*filter_sepia(t_image *image)
{
	size_t		i;
	size_t		total_size;
	t_color		*current_pixel;
	t_vector3	t;

	total_size = image->res.x * image->res.y;
	i = 0;
	while (i < total_size)
	{
		current_pixel = (t_color *)&image->img_data[i];
		t.x = 0.393 * current_pixel->r + 0.769 * current_pixel->g
			+ 0.189 * current_pixel->b;
		t.y = 0.349 * current_pixel->r + 0.686 * current_pixel->g
			+ 0.168 * current_pixel->b;
		t.z = 0.272 * current_pixel->r + 0.534 * current_pixel->g
			+ 0.131 * current_pixel->b;
		current_pixel->r = t.x > 255 ? 255 : t.x;
		current_pixel->g = t.y > 255 ? 255 : t.y;
		current_pixel->b = t.z > 255 ? 255 : t.z;
		i++;
	}
	return (image);
}

t_image	*filter_inv(t_image *image)
{
	size_t	i;
	size_t	total_size;
	t_color	*current_pixel;

	total_size = image->res.x * image->res.y;
	i = 0;
	while (i < total_size)
	{
		current_pixel = (t_color *)&image->img_data[i];
		current_pixel->r = 1 - current_pixel->r;
		current_pixel->g = 1 - current_pixel->g;
		current_pixel->b = 1 - current_pixel->b;
		i++;
	}
	return (image);
}
