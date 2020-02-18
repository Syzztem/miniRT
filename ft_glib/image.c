/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 10:42:42 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/17 16:23:10 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void
	write_int(int nb, int fd)
{
	char	*out;
	int		i;

	i = -1;
	out = (char *)&nb;
	while (++i < 4)
		write(fd, &out[i], 1);
}

size_t
	f_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char
	*add_extension(char *filename)
{
	char *out;
	char *str;

	out = malloc(sizeof(char) * (f_strlen(filename) + 5));
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
	generate_image(t_vector2 res, void *mlx_ptr)
{
	t_image out;

	out.img_ptr = mlx_new_image(mlx_ptr, res.x, res.y);
	out.res = res;
	out.img_data = (int *)mlx_get_data_addr(out.img_ptr,
		(int *)&out.bpp, &out.size_line, &out.endian);
	return (out);
}

int
	create_bitmap(t_image image, char *filename)
{
	int		fd;
	int		total_size;
	int		line_size;
	char	*img_data;
	int		i;

	filename = add_extension(filename);
	line_size = (image.res.x * image.bpp + 31) / 32 * 4;
	total_size = line_size * image.res.y;
	fd = open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	img_data = (char *)(image.img_data);
	write(fd, "BM", 2);
	write_int(total_size + 54, fd);
	write(fd, "\0\0\0\0\x36\0\0\0\x28\0\0\0", 12);
	write_int(image.res.x, fd);
	write_int(image.res.y, fd);
	write(fd, "\1\0", 2);
	write(fd, &image.bpp, 1);
	write(fd, "\0\0\0\0\0", 5);
	write_int(total_size, fd);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
	i = total_size;
	while (i > 0)
	{
		i -= line_size;
		write(fd, img_data + i, line_size);
	}
	return (0);
}
