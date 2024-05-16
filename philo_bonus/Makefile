NAME=philo_bonus
SRC= philo_bonus.c\
	utils.c\
	parse/parse_utils.c\
	parse/parse.c\
	init.c\
	dead.c\
	forks.c\
	process.c\
	time.c\
	ft_itoa.c\
	ft_strlen.c\
	ft_strjoin.c\
	ft_strdup.c\

OBJ=$(SRC:.c=.o)
CC=cc
FLAGS=-Wall -Wextra -Werror
HEADER=philo_bonus.h
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