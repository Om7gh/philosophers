NAME=philo
SRC=philosopher.c\
	utils.c\
	parse/parse_utils.c\
	parse/parse.c\
	init.c\
	simulation/dinner.c\
	simulation/dinner_utils.c\
	simulation/tmp_thread.c

OBJ=$(SRC:.c=.o)
CC=cc
FLAGS=-Wall -Wextra -Werror
HEADER=philosopher.h
%.o:%.c $(HEADER)
		$(CC) $(FLAGS) -c $< -o $@
all:$(NAME)
$(NAME):$(OBJ)
		$(CC) $(OBJ) -o $(NAME)
clean:
		rm -f $(OBJ)
fclean:clean
		rm -f $(NAME)
re:fclean all
.PHONY:clean