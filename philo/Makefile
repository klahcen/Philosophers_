
CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror 
NAME	=	philo
src		=	ft_atoi.c ft_danedata.c ft_philosophers.c ft_usleep.c main.c ft_check.c
OBJC	=   ${src:.c=.o}

all: $(NAME)

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME)

clean:
	rm -rf $(OBJC)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

