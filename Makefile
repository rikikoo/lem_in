# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 15:30:07 by rkyttala          #+#    #+#              #
#    Updated: 2021/04/06 10:10:38 by rkyttala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = src/
O = obj/
I = includes/

SRC =	$Smain.c \
		$Shash.c \
		$Sparse_rooms.c \
		$Sparse_links.c \
		$Sgraph.c


OBJ = $(SRC:$S%=$O%.o)

INC = $I

LIB = libft/libft.a

CCOMP = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = lem-in

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir -p $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	$(CCOMP) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME): $(OBJ)
#	@make -C libft/
#	@make -C libft/ clean
	$(CCOMP) $(CFLAGS) $^ $(LIB) -o $@ -I $(INC)

clean:
	rm -rf $O

fclean: clean
	rm -f $(NAME)

re: fclean all
