# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 16:41:09 by lorbke            #+#    #+#              #
#    Updated: 2023/02/07 07:31:31 by fyuzhyk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SHELL macro
SHELL := /bin/bash

# colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
RESET := \033[0m

# name macros
NAME := minishell

# command macros
CC := cc
AR := ar rcs
RM := rm -f
CFLAGS := #-Wall -Wextra -Werror

# library macros
LIB_PATH := lib
LFT_PATH := $(LIB_PATH)/libft
LFT_LIB := ft
LFT_LINK := -L$(LFT_PATH) -l$(LFT_LIB)
LEXER_PATH := $(LIB_PATH)/lexer
LEXER_LIB := lexer
LEXER_LINK := -L$(LEXER_PATH) -l$(LEXER_LIB)
PARSER_PATH := $(LIB_PATH)/parser
PARSER_LIB := parser
PARSER_LINK := -L$(PARSER_PATH) -l$(PARSER_LIB)
EXECUTER_PATH := $(LIB_PATH)/executer
EXECUTER_LIB := executer
EXECUTER_LINK := -L$(EXECUTER_PATH) -l$(EXECUTER_LIB)
ENV_PATH := $(LIB_PATH)/env
ENV_LIB := env
ENV_LINK := -L$(ENV_PATH) -l$(ENV_LIB)
RDLN_LIB := readline

# src and obj files macros
SRC_PATH := src
OBJ_PATH := obj
SRC := $(wildcard $(SRC_PATH)/*.c) $(wildcard $(SRC_PATH)/*/*.c)
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# VPATH
VPATH := $(SRC_PATH) $(SRC_PATH)/debugger $(SRC_PATH)/builtins

# file targets
$(NAME): $(OBJ_PATH) $(OBJ)
	@$(MAKE) -C $(LFT_PATH)
	@$(MAKE) -C $(LEXER_PATH)
	@$(MAKE) -C $(PARSER_PATH)
	@$(MAKE) -C $(EXECUTER_PATH)
	@$(MAKE) -C $(ENV_PATH)
	@echo -e -n "$(BLUE)Creating: minishell executable: $(RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) $(EXECUTER_LINK) $(ENV_LINK) -l$(RDLN_LIB) -o $(NAME)
	@echo -e "$(GREEN)make: minishell success!$(RESET)"
# inc when on macbook
# -L/opt/homebrew/Cellar/readline/8.2.1/lib

dev: $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) dev.o $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) $(EXECUTER_LINK) $(ENV_LINK) -l$(RDLN_LIB) -o dev
# inc when on macbook
# -L/opt/homebrew/Cellar/readline/8.2.1/lib

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile $(SRC_PATH)/minishell.h $(SRC_PATH)/debugger.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(CFLAGS) -I$(LFT_PATH) -I$(LEXER_PATH) -I$(PARSER_PATH) -I$(EXECUTER_PATH) -I$(ENV_PATH) -c $< -o $@
# inc when on macbook
# -I/opt/homebrew/Cellar/readline/8.2.1/include

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	@cd $(LFT_PATH) && $(MAKE) fclean
	@cd $(LEXER_PATH) && $(MAKE) fclean
	@cd $(PARSER_PATH) && $(MAKE) fclean
	@cd $(EXECUTER_PATH) && $(MAKE) fclean
	@cd $(ENV_PATH) && $(MAKE) fclean
	$(RM) $(NAME)
	@echo -e "$(RED)make: minishell cleaned!$(RESET)"

re: fclean all

debug: CFLAGS += -O0 -DDEBUG -g
debug: clean all
	@$(MAKE) clean

test:
	@rm -f tester
	@$(MAKE) -C $(LFT_PATH)
	@$(MAKE) -C $(LEXER_PATH)
	@$(MAKE) -C $(PARSER_PATH)
	@$(MAKE) -C $(ENV_PATH)
	@$(MAKE) -C $(EXECUTER_PATH
	$(CC) -O0 -DDEBUG -g tester.c executer/executer.c executer/executer_path.c $(SRC_PATH)/debugger/debugger.c -I$(SRC_PATH) -I$(LFT_PATH) \
	-I$(LEXER_PATH) -I$(PARSER_PATH) -I$(ENV_PATH) -Iexecuter $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) $(ENV_LINK) -l$(RDLN_LIB) -o tester

.PHONY: all clean fclean re
