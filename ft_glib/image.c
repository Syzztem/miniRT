/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 10:42:42 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/11 12:08:52 by lothieve         ###   ########.fr       */
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

char
	ft_reverse_bits(char byte)
{
	char tmp;

	tmp = byte >> 4;
	byte = byte << 4;
	byte |= tmp;
	return (byte);
}

int
	create_bitmap(t_image image, char *filename)
{
	int		fd;
	int		total_size;
	char	*img_data;

	total_size = (image.res.x * image.res.y * image.bpp + 31) / 32 * 4;
	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IWUSR);
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
	write(fd, img_data, total_size);
	return (0);
}
