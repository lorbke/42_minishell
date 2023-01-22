# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 16:41:09 by lorbke            #+#    #+#              #
#    Updated: 2023/01/22 20:56:13 by lorbke           ###   ########.fr        #
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
RDLN_LIB := readline

# src and obj files macros
SRC_PATH := src
OBJ_PATH := obj
SRC := $(wildcard $(SRC_PATH)/*.c) $(wildcard $(SRC_PATH)/*/*.c)
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# VPATH
VPATH := $(SRC_PATH) $(SRC_PATH)/debugger

# file targets
$(NAME): $(OBJ_PATH) $(OBJ)
	@$(MAKE) -C $(LFT_PATH)
	@$(MAKE) -C $(LEXER_PATH)
	@$(MAKE) -C $(PARSER_PATH)
	@echo -e -n "$(BLUE)Creating: minishell executable: $(RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) -l$(RDLN_LIB) -o $(NAME)
	@echo -e "$(GREEN)make: minishell success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile $(SRC_PATH)/minishell.h $(SRC_PATH)/debugger.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(CFLAGS) -I$(LFT_PATH) -I$(LEXER_PATH) -I$(PARSER_PATH) -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	@cd $(LFT_PATH) && $(MAKE) fclean
	@cd $(LEXER_PATH) && $(MAKE) fclean
	@cd $(PARSER_PATH) && $(MAKE) fclean
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
	$(CC) -O0 -DDEBUG -g tester.c $(SRC_PATH)/debugger/debugger.c -I$(SRC_PATH) -I$(LFT_PATH) \
	-I$(LEXER_PATH) -I$(PARSER_PATH) $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) -l$(RDLN_LIB) -o tester

.PHONY: all clean fclean re
