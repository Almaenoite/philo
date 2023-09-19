# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 05:24:25 by tbae              #+#    #+#              #
#    Updated: 2023/09/19 23:03:11 by tbae             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c\
	routine.c\
	utils.c\
	init.c \
	libft_lite.c \
	check.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -g3 -Wall -Werror -Wextra -g

all: ${NAME}

${NAME}: ${OBJS}
	cc -g3 ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re : fclean all

.PHONY: clean fclean all re

