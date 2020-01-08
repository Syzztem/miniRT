/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 10:42:42 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/08 11:27:03 by lothieve         ###   ########.fr       */
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
//	printf("%d => %x|%x|%x|%x\n", nb, out[0], out[1], out[2], out[3]);
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

int	create_bitmap(t_image image, char *filename)
{
	int fd;
	int total_size;
	char *img_data;

	total_size = (image.width * image.height * image.bpp + 31) / 32 * 4;
	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IWUSR);
	img_data = (char *)(image.img_data);
	write(fd, "BM", 2);
	write_int(total_size + 54, fd);
	write(fd, "\0\0\0\0\x36\0\0\0\x28\0\0\0", 12);
	write_int(image.width, fd);
	write_int(image.height, fd);
	write(fd, "\1\0", 2);
	write(fd, &image.bpp, 1);
	write(fd, "\0\0\0\0\0", 5);
	write_int(total_size, fd);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
	write(fd, img_data, total_size);
	return (0);
}