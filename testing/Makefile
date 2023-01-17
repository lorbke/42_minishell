

NAME = test

OBJ_PATH = obj

SRC = $(wildcard src/*.c)
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

CC = cc -g

all: makedir $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_PATH)/%.o: src/%.c
	$(CC) -c $< -o $@

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re: clean all

.PHONY: clean re
