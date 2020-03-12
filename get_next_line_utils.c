/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:23:14 by lothieve          #+#    #+#             */
/*   Updated: 2020/03/11 17:20:43 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int
	ft_indexof(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char
	*ft_strndup(const char *src, int n)
{
	char	*dup;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(src);
	len = len > n ? n + 1 : len + 1;
	if (!(dup = malloc(sizeof(char) * len)))
		return (NULL);
	while (src[++i] && i < n)
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}

int
	set_buffers(char *out, char **last_line, char **line, int rv)
{
	int i;
	int len;

	if (!out || (((i = ft_indexof(out, '\n')) == -1) && rv == BUFFER_SIZE))
		return (0);
	len = ft_strlen(out);
	*line = ft_strndup(out, (i == -1 ? len : i));
	if (i == -1)
		*last_line = NULL;
	else
		*last_line = ft_strndup(out + i + 1, ft_strlen(out));
	free(out);
	return (1);
}
