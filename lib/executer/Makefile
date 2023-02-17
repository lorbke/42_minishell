# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 13:54:25 by lorbke            #+#    #+#              #
#    Updated: 2023/02/16 09:14:58 by fyuzhyk          ###   ########.fr        #
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

# name macro
NAME := libexecuter.a

# command macros
CC := cc
AR := ar rcs
RM := rm -f
ADD_FLAGS := #-g -fsanitize=address,undefined
FLAGS := -Wall -Wextra -Werror

# header macros
LFT_INC := ../libft
LEXER_INC := ../lexer
PARSER_INC := ../parser

# src and obj files macros
OBJ_PATH := obj
SRC_PATH := src
SRC := $(wildcard $(SRC_PATH)/*.c)
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# VPATH
VPATH := $(SRC_PATH)

# file targets
$(NAME): $(OBJ_PATH) $(OBJ)
	@echo -e -n "$(BLUE)Creating: executer library: $(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo -e "$(GREEN)make: executer success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile executer.h $(SRC_PATH)/executer_private.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(FLAGS) $(ADD_FLAGS) -I$(LFT_INC) -I$(LEXER_INC) -I$(PARSER_INC) -I. -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(RED)make: executer cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
