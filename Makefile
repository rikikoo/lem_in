# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 15:30:07 by rkyttala          #+#    #+#              #
#    Updated: 2021/07/07 15:12:22 by rkyttala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = src/
O = obj/
I = includes/
L = libft/

SRC =	$(S)main.c \
		$(S)inits.c \
		$(S)input.c \
		$(S)hash.c \
		$(S)vertices.c \
		$(S)edges.c \
		$(S)graph.c \
		$(S)bfs.c \
		$(S)utils.c \
		$(S)free.c \
		$(S)sort.c \
		$(S)output.c

OBJ = $(SRC:$S%=$O%.o)
INC = $(I)
LIB = $(L)libft.a
LIBINC = $(L)$(I)
CCOMP = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = lem-in

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir -p $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	$(CCOMP) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(LIBINC)

$(NAME): $(OBJ)
#	@make -C $(L)
#	@make -C $(L) clean
	$(CCOMP) $(CFLAGS) $^ $(LIB) -o $@ -I $(INC) -I $(LIBINC)

debug:
	gcc -g -fsanitize=address src/*.c libft/libft.a -I $(INC) -I $(LIBINC)

clean:
	rm -rf $O
	rm -rf a.out*

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all
