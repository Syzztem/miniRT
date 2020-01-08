# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:37:59 by lothieve          #+#    #+#              #
#    Updated: 2020/01/07 16:12:37 by lothieve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = atoi.c ft_strncmp.c get_next_line.c get_next_line_utils.c mini_rt.c parser.c parser2.c sphere.c ft_glib/color_functions.c ft_glib/v3f_operations.c ft_glib/v3f_values.c ft_glib/basic_calc.c ft_glib/ray_functions.c light.c ft_glib/matrix.c plane.c ft_glib/image.c ft_glib/ft_memcpy.c

OBJS = ${SRCS:.c=.o}

NAME = mini_rt

CFLAGS = -Wall -Wextra -Werror -g

LFLAGS = -lmlx -framework OpenGL -framework AppKit -g 

CC = clang

RM = rm -f

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				${CC} ${LFLAGS} -o ${NAME} ${OBJS}

clean:
				${RM} ${OBJS}

fclean:		clean
				${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
