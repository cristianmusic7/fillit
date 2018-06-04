# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfranco <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 10:55:49 by cfranco            #+#    #+#              #
#    Updated: 2018/06/04 02:40:11 by cfranco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
NAME_LIB = libft.a
CC = gcc
HEADERS = -I ./includes \
		  -I ./libft

FLAGS = -Wall -Wextra -Werror -o
LIBFT = -L libft -lft
DEPENDENCY = fillit.c \
			 print.c \
			 manipulate_bits.c \
			 check.c \
			 fillit_2.c

OBJ = $(patsubst libft/%.c, %.o, $(LIBFT))

all: $(NAME)

$(NAME): $(DEPENDENCY1)
	make re -C libft/
	$(CC) $(FLAGS) $(NAME) $(HEADERS) $(DEPENDENCY) $(LIBFT)

clean:
	rm -f *.o 

fclean:
	make fclean -C libft/
	rm -f $(NAME) $(NAME_LIB) *.o

re: fclean all

