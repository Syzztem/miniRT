/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:56:25 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/16 16:40:42 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char
	*ft_strxtend(char *s1, char *s2)
{
	char	*out;
	char	*c;
	char	*s1c;
	size_t	len;

	if (!*s2)
		return (s1);
	len = ft_strlen(s2) + ft_strlen(s1) + 1;
	if (!(out = malloc(sizeof(char) * len)))
		return (NULL);
	s1c = s1;
	c = out;
	while (s1c && *s1c)
		*c++ = *s1c++;
	while (*s2)
		*c++ = *s2++;
	*c = 0;
	free(s1);
	return (out);
}

int
	empty_string(char **line)
{
	*line = malloc(sizeof(char));
	*line = 0;
	return (-1);
}

int
	get_next_line2(int fd, char **line, char *buf, int rv)
{
	char		*out;
	static char	*last_line = NULL;

	out = last_line;
	if (out && set_buffers(out, &last_line, line, BUFFER_SIZE))
		return (1);
	while ((rv = read(fd, buf, BUFFER_SIZE)) == BUFFER_SIZE)
	{
		out = ft_strxtend(out, buf);
		if (set_buffers(out, &last_line, line, rv))
			return (1);
	}
	if (rv == -1)
		return (empty_string(line));
	buf[rv] = 0;
	out = ft_strxtend(out, buf);
	rv = set_buffers(out, &last_line, line, rv);
	if (!rv)
		*line = ft_strndup("", 1);
	return (rv && last_line ? 1 : 0);
}

int
	get_next_line(int fd, char **line)
{
	char	*buf;
	int		rv;

	if (!line)
		return (-1);
	if (BUFFER_SIZE <= 0 || fd == 1 || fd == 2)
		return (empty_string(line));
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 2))))
		return (0);
	buf[BUFFER_SIZE] = 0;
	*buf = 0;
	rv = get_next_line2(fd, line, buf, 0);
	free(buf);
	return (rv);
}
