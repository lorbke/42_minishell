

NAME = test

LEXER_PATH = lexer
PARSER_PATH = parser
DEBUGGER_PATH = debugger

SRC_PATH = src
OBJ_PATH = obj

INC = $(SRC_PATH)
INC_LEXER = $(LEXER_PATH)
INC_PARSER = $(PARSER_PATH)
INC_DEBUGGER = $(DEBUGGER_PATH)

VPATH = $(SRC_PATH) $(LEXER_PATH)/src $(PARSER_PATH)/src $(DEBUGGER_PATH)/src

SRC = $(wildcard */*.c) $(wildcard */*/*.c)
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

CC = cc -g

all: makedir $(NAME)
	@echo VPATH: $(VPATH)
	@echo SRC: $(SRC)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_PATH)/%.o: %.c
	$(CC) -I$(INC) -I$(INC_LEXER) -I$(INC_PARSER) -I$(DEBUGGER_PATH) -c $< -o $@

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re: clean all

.PHONY: clean re
