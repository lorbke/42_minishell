

NAME = testing

OBJ_PATH = obj

SRC = $(wildcard *.c)
OBJ = $(addprefix $(OBJ_PATH)/,$(patsubst %.c,%.o,$(SRC)))

CC = gcc -g

all: makedir $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_PATH)/%.o: %.c
	$(CC) -c $< -o $@

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re: clean all

.PHONY: clean re
