# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 18:44:15 by fyuzhyk           #+#    #+#              #
#    Updated: 2023/02/18 18:45:59 by fyuzhyk          ###   ########.fr        #
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
NAME := libgnl.a

# command macros
CC := cc
AR := ar rcs
RM := rm -f
ADD_FLAGS := #-g -fsanitize=address,undefined
FLAGS := -Wall -Wextra -Werror

# header macros
LFT_INC := ../libft

# src and obj files macros
OBJ_PATH := obj
SRC_PATH := src
SRC := $(wildcard $(SRC_PATH)/*.c)
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# VPATH
VPATH := $(SRC_PATH)

# file targets
$(NAME): $(OBJ_PATH) $(OBJ)
	@echo -e -n "$(BLUE)Creating: gnl library: $(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo -e "$(GREEN)make: gnl success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile get_next_line.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(FLAGS) $(ADD_FLAGS) -I$(LFT_INC) -I. -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(RED)make: gnl cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
