CC=gcc
NAME=philo
CFLAGS=-Wall -Wextra -Werror
LIB_DIR=../libft/
LIB=libft.a
LIB_INC=libft.h
INC = philo_bonus.h

SRC =	main_bonus.c			\
		eat_bonus.c				\
		init_bonus.c			\
		utils_bonus.c			\
		utils2_bonus.c	

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