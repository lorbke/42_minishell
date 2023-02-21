# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 13:54:25 by lorbke            #+#    #+#              #
#    Updated: 2023/02/21 18:37:18 by lorbke           ###   ########.fr        #
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
NAME := libparser.a

# command macros
CC := cc
AR := ar rcs
RM := rm -f
ADD_FLAGS := #-g -fsanitize=address,undefined
FLAGS := -g -Wall -Wextra -Werror

# library macros
LIB_PATH := ../
LFT_PATH := $(LIB_PATH)/libft
LFT_LIB := ft
LFT_LINK := -L$(LFT_PATH) -l$(LFT_LIB)

# header macros
LEXER_INC := ../lexer

# src and obj files macros
OBJ_PATH := obj
SRC_PATH := src
SRC := $(wildcard $(SRC_PATH)/*.c)
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# VPATH
VPATH := $(SRC_PATH)

# file targets
$(NAME): $(OBJ_PATH) $(OBJ)
	@$(MAKE) -C $(LFT_PATH)
	@echo -e -n "$(BLUE)Creating: parser library: $(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo -e "$(GREEN)make: parser success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile parser.h $(SRC_PATH)/private_parser.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(FLAGS) $(ADD_FLAGS) -I$(LFT_PATH) -I$(LEXER_INC) -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(RED)make: parser cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
