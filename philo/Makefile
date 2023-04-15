CC=gcc
NAME=philo
CFLAGS=-Wall -Wextra -Werror
LIB_DIR=../libft/
LIB=libft.a
LIB_INC=libft.h
INC = philo.h

SRC =	main.c			\
		eat.c			\
		init.c			\
		utils.c			\
		utils2.c	

SRC_BNS =

OBJ=$(SRC:.c=.o)

OBJ_BNS=$(SRC_BNS:.c=.o)

all:
	@$(MAKE) $(NAME)

%.o: %.c $(INC) 
	@echo "Compilant $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) 
	@echo "Enllaçant $@"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ) $(OBJ_BNS)

fclean: clean
	rm -f $(NAME)

re: fclean all	

.PHONY: clean fclean all re bonus