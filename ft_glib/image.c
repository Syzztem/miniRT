/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 10:42:42 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/03 18:26:29 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void
	image_pixel_put(t_image *image, int x, int y, int color)
{
	image->img_data[x + y * image->size_line / sizeof(int)] = color;
}

char
	*add_extension(char *filename)
{
	char *out;
	char *str;

	out = malloc(sizeof(char) * (ft_strlen(filename) + 5));
	str = out;
	while (*filename)
		*str++ = *filename++;
	*str++ = '.';
	*str++ = 'b';
	*str++ = 'm';
	*str++ = 'p';
	*str++ = '\0';
	return (out);
}

t_image
	*generate_image(t_vector2 res, void *mlx_ptr)
{
	t_image *out;

	out = malloc(sizeof(t_image));
	if (!(out->img_ptr = mlx_new_image(mlx_ptr, res.x, res.y)))
		exit(1);
	out->res = res;
	out->img_data = (int *)mlx_get_data_addr(out->img_ptr,
		(int *)&out->bpp, &out->size_line, &out->endian);
	return (out);
}

int
	write_image_data(int fd, char *img_data, int line_size, int total_size)
{
	int		i;

	i = total_size;
	while (i > 0)
	{
		i -= line_size;
		write(fd, img_data + i, line_size);
	}
	return (0);
}

int
	create_bitmap(t_image image, char *filename)
{
	int		fd;
	int		total_size;
	int		line_size;
	char	*img_data;

	filename = add_extension(filename);
	line_size = (image.res.x * image.bpp + 31) / 32 * 4;
	total_size = line_size * image.res.y;
	fd = open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	img_data = (char *)(image.img_data);
	write(fd, "BM", 2);
	write(fd, (&total_size + 54), 4);
	write(fd, "\0\0\0\0\x36\0\0\0\x28\0\0\0", 12);
	write(fd, &image.res.x, 4);
	write(fd, &image.res.y, 4);
	write(fd, "\1\0", 2);
	write(fd, &image.bpp, 1);
	write(fd, "\0\0\0\0\0", 5);
	write(fd, &total_size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
	return (write_image_data(fd, img_data, line_size, total_size));
}
