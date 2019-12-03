/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:56:23 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/16 16:23:37 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_file
{
	int				fd;
	char			*last_line;
	struct s_file	*next;
}				t_file;

int				get_next_line(int fd, char **line);
int				ft_indexof(const char *s, char c);
int				set_buffers(char *out, char **last_line, char **line, int rv);
size_t			ft_strlen(const char *s);
char			*ft_strndup(const char *src, int n);

#endif
