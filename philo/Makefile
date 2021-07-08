NAME	=	philo
SRC		=	main.c ft_atoi.c
OBJ		=	main.o ft_atoi.o

all		:	$(NAME)
$(NAME) : $(SRC)
			gcc -Wall -Wextra -Werror $(SRC) -o $(NAME)
clean	:
		rm -f $(NAME)
fclean	: clean	
re		: fclean
		make all