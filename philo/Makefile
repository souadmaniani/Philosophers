NAME	=	philo
SRC		=	main.c ft_atoi.c utils.c philo_action.c
OBJ		=	main.o ft_atoi.o utils.o philo_action.o

all		:	$(NAME)
$(NAME) : $(SRC)
			@gcc $(SRC) -o $(NAME)  -pthread
clean	:
		@rm -rf $(NAME)
		@rm -rf philo.dSYM
fclean	: clean	
re		: fclean
		@make all