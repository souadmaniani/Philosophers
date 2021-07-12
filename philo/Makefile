NAME	=	philo
SRC		=	main.c ft_atoi.c utils.c
OBJ		=	main.o ft_atoi.o utils.o

all		:	$(NAME)
$(NAME) : $(SRC)
			@gcc -Wall -Wextra -Werror $(SRC) -o $(NAME)  -pthread
clean	:
		@rm -f $(NAME)
fclean	: clean	
re		: fclean
		@make all