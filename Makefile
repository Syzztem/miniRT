# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:37:59 by lothieve          #+#    #+#              #
#    Updated: 2019/12/01 16:31:13 by lothieve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = atoi.c ft_strncmp.c get_next_line.c get_next_line_utils.c mini_rt.c parser.c parser2.c trace.c ft_glib/color_functions.c ft_glib/v3f_operations.c ft_glib/v3f_values.c ft_glib/basic_calc.c

OBJS = ${SRCS:.c=.o}

NAME = mini_rt

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -lmlx -framework OpenGL -framework AppKit 

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
