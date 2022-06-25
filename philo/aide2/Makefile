# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/12 17:17:53 by mdouiri           #+#    #+#              #
#    Updated: 2022/06/12 17:18:30 by mdouiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philosopher.c lets_do_it.c print.c live.c init.c main.c

OBJS = ${SRC:.c=.o}

RM = rm -f

CC = cc

CFLAGS = -pthread -Wall -Wextra -Werror -g

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all: ${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
