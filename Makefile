SRC=main.c list.c op.c instr.c
SRC_PUSH_SWAP=push_swap.c util.c rotate.c algo.c
SRC_CHECKER=checker.c
INC=push_swap.h
OBJ=$(SRC:.c=.o)
OBJ_PUSH_SWAP=$(SRC_PUSH_SWAP:.c=.o)
OBJ_CHECKER=$(SRC_CHECKER:.c=.o)
CFLAGS=-Wall -Wextra -Werror -O3 -flto
NAME=push_swap

all: $(NAME) checker

$(NAME): $(OBJ) $(OBJ_PUSH_SWAP)
	$(CC) $(CFLAGS) -o $@ $^

checker: $(OBJ) $(OBJ_CHECKER)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< -c

clean:
	rm -f $(OBJ) $(OBJ_PUSH_SWAP) $(OBJ_CHECKER)

fclean: clean
	rm -f $(NAME) checker

re: fclean all
