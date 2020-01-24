##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile for 102 architect
##

############ SOURCES ###########
SRC	=	src/intersection.c
MAIN	=	main.c
################################

############ FLAGS #############
CPPFLAGS	+= -lm -I include
################################

############ BINARY ############
NAME	=	104intersection
################################

.PHONY: all
all:	$(NAME)
$(NAME):
	gcc -o $(NAME) $(MAIN) $(SRC) $(CPPFLAGS) $(CFLAGS)

.PHONY: debug
debug: CPPFLAGS += -g3
debug: $(NAME)

.PHONY:
clean:
	rm -f *~
.PHONY:
fclean: clean
	rm -f $(NAME)

.PHONY:
re:	fclean all
