# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:37:59 by lothieve          #+#    #+#              #
#    Updated: 2020/08/13 15:08:13 by lothieve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_glib/atoi.c create_elems.c create_elems2.c create_elems3.c cylinder.c exit.c ft_strncmp.c key_functions.c light.c mini_rt.c parser.c parser2.c plane.c sphere.c square.c trace.c triangle.c ft_glib/basic_calc.c ft_glib/color_functions.c ft_glib/color_functions2.c ft_glib/filters.c ft_glib/ft_memcpy.c ft_glib/get_next_line.c ft_glib/get_next_line_utils.c ft_glib/image.c ft_glib/matrix.c ft_glib/ray_functions.c ft_glib/v3f_operations.c ft_glib/v3f_operations2.c ft_glib/v3f_values.c


NAME = miniRT

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -DLINUX

COMMAND		= clang

RM		= /bin/rm -f


LIB		= ./minilibx-linux/libmlx.a


INCLUDE		= -L. minilibx-linux/libmlx.a -lXext -lX11 -lm -lbsd -lpthread

MLX		= ./minilibx-linux


all: ${NAME}

${NAME}:	minilibx ${OBJS}
		${COMMAND} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} ${LIB}

.c.o:
		$(COMMAND) -w $(CFLAGS) ${INCLUDE} -c $< -o ${<:.c=.o} ${LIB}

minilibx:
		$(MAKE) -C ./minilibx-linux

bonus:		CFLAGS += -DBONUS
bonus:		${NAME}

clean:
		$(MAKE) -C ./minilibx-linux/. clean
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}
		${RM} ./minilibx-linux/libmlx.a

re:		fclean all

.PHONY: all clean fclean re
