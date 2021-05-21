# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 15:30:07 by rkyttala          #+#    #+#              #
#    Updated: 2021/05/21 12:58:48 by rkyttala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = src/
O = obj/
I = includes/
L = libft/

SRC =	$Smain.c \
		$Shash.c \
		$Sparse_vertices.c \
		$Sparse_edges.c \
		$Sgraph.c


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
	@make -C libft/
	@make -C libft/ clean
	$(CCOMP) $(CFLAGS) $^ $(LIB) -o $@ -I $(INC) -I $(LIBINC)

debug:
	gcc -g -fsanitize=address src/*.c libft/libft.a

clean:
	rm -rf $O

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all
