##
## EPITECH PROJECT, 2018
## CCP_plazza_2018
## File description:
## Makefile
##

NAME		=	plazza

SRCS		=	./src/plazza.cpp    \
                ./src/reception.cpp

OBJS		=	$(SRCS:.cpp=.o)
INCL		=	-I./include

CC			=	g++
RM			=	rm -f
CFLAGS		=   -W -Wall -Wextra

.c.o	:
	@$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf " \033[34m[Compilation]\033[39m %s\n" $<

all	:	$(OBJS)
		@$(CC) $(OBJS) -o $(NAME)
		@printf "\n \033[33m[Message]\033[39m Server compilation done\n"

clean	:
	@$(RM) *~ $(OBJS)
	@printf " \033[31m[Delete] \033[39m%s\n" $(OBJS)

fclean	:	clean
	@$(RM) $(NAME)
	@printf "\n \033[31m[Delete] \033[39m%s\n\n" $(NAME)

re	:	fclean all