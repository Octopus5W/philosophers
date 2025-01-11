NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC =	src/main.c src/parsing.c src/actions.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all