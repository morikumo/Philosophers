# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabid <mabid@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/18 19:59:16 by mabid             #+#    #+#              #
#    Updated: 2022/06/25 15:02:33 by mabid            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 	= test.c routine.c parsing.c\
			

OBJS			= $(SRCS:.c=.o)

NAME			= philo

CFLAGS			= -pthread

RM				= rm -f

CC				= gcc

AR				= ar rcs

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L.
				@echo -ne '\033[32m                            (0%)\r'
				@sleep 0.2
				@echo -ne '#####                      (33%)\r'
				@sleep 0.2
				@echo -ne '#############              (66%)\r'
				@sleep 0.2
				@echo -ne '#######################   (100%)\r'
				@echo -ne '\n'
				@echo "\033[33mC'est compilé !"

all:			$(NAME)

clean:
				@$(RM) $(OBJS)
				@echo -ne '\033[36m#######################   (100%)\r'
				@sleep 0.2
				@echo -ne '#############              (66%)\r'
				@sleep 0.2
				@echo -ne '#####                      (33%)\r'
				@sleep 0.2
				@echo -ne '                            (0%)\r'
				@echo -ne '\n'
				@echo "\033[33mC'est clean !"

fclean:			clean
				@$(RM) $(NAME) 
				@echo -ne '\033[34m#######################   (100%)\r'
				@sleep 0.2
				@echo -ne '#############              (66%)\r'
				@sleep 0.2
				@echo -ne '#####                      (33%)\r'
				@sleep 0.2
				@echo -ne '                            (0%)\r'
				@echo -ne '\n'
				@echo "\033[33mC'est fclean !"

re:				fclean all