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
ERASE		:=	\033[2K\r
BLUE		:=	\033[34m
YELLOW		:=	\033[33m
GREEN		:=	\033[32m
END			:=	\033[0m
%.o:%.c $(HEADER)
		$(CC) $(FLAGS) -c $< -o $@
		printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"
all:$(NAME)
$(NAME):$(OBJ)
		$(CC) $(OBJ) -o $(NAME)
		printf "$(ERASE)$(GREEN)$@ made\n$(END)"
clean:
		printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
		rm -f $(OBJ)
fclean:clean
		printf "$(YELLOW)$(NAME) removed$(END)\n"
		rm -f $(NAME)
re:fclean all
.PHONY:clean
.SILENT: