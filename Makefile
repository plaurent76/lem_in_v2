# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eviana <eviana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/15 11:23:59 by eviana            #+#    #+#              #
#    Updated: 2019/07/19 15:01:23 by eviana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -g -Wall -Wextra # -Werror
NAME = lem_in

RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
PURPLE = "\033[0;35m"
CYAN = "\033[0;36m"
MAGENTA = "\033[0;35;1m"
RESET = "\033[0m"

SRC = 	lem_in.c utils.c get_input.c get_data.c filling.c delete.c alloc.c bfs.c \
		ek.c newpath.c choice_path.c new_bfs.c

HEADER = ./includes/

LIB = libft/libft.a

OBJ = $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
	@make -C libft
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) -I $(HEADER) $(LIB)
	@echo $(CYAN)*****$(GREEN)lem_in compiled$(CYAN)*****

%.o: %.c
	@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

.PHONY: clean fclean

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all
