NAME	=	philo
SRC		=	main.c ft_atoi.c
OBJ		=	main.o ft_atoi.o

all		:	$(NAME)
$(NAME) : $(SRC)
			@gcc  $(SRC) -o $(NAME)  -pthread
clean	:
		@rm -f $(NAME)
fclean	: clean	
re		: fclean
		@make all