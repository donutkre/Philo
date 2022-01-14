NAME = philo

SRC = main.c ft_atoi.c start.c routine.c time.c make.c

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) -lpthread

clean: 
	echo "No object files to remove."

fclean:
	rm -rf $(NAME)

re: fclean all

noflags:
	gcc $(SRC) -o $(NAME)