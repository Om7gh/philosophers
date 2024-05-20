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