##
## EPITECH PROJECT, 2019
## makefile
## File description:
## made by Martin Vantalon
##

CC=     	gcc

NAME=		test

SRC=		main.c

OBJ=            $(SRC:.c=.o)

CFLAGS=         -lpthread -Wall -Wextra -g3

all:            $(NAME)

$(NAME):        $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)
clean:
		rm -f $(OBJ)
fclean:         clean
		rm -f $(NAME)

re:         fclean all

