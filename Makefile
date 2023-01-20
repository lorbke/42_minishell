# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 16:41:09 by lorbke            #+#    #+#              #
#    Updated: 2023/01/20 17:27:44 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SHELL macro
SHELL := /bin/bash

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

# default target
default: makedir all

# file targets
$(NAME): libraries $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) -l$(RDLN_LIB) -o $(NAME)
	@echo "make: minishell success!"

$(OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) -I$(LFT_PATH) -I$(LEXER_PATH) -I$(PARSER_PATH) -c $< -o $@

# phony targets
all: $(NAME)

makedir:
	@mkdir -p $(OBJ_PATH)

libraries:
	@$(MAKE) -C $(LFT_PATH)
	@$(MAKE) -C $(LEXER_PATH)
	@$(MAKE) -C $(PARSER_PATH)

clean:
	@echo "minishell: "
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@cd $(LFT_PATH) && $(MAKE) fclean
	@cd $(LEXER_PATH) && $(MAKE) fclean
	@cd $(PARSER_PATH) && $(MAKE) fclean

re: fclean makedir all

debug: CFLAGS += -O0 -DDEBUG -g
debug: clean default

.PHONY: all clean fclean re
