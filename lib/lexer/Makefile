# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 13:54:25 by lorbke            #+#    #+#              #
#    Updated: 2023/01/18 16:47:48 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SHELL macro
SHELL := /bin/bash

# name macro
NAME := liblexer.a

# command macros
CC := cc
AR := ar rcs
RM := rm -f
ADD_FLAGS := #-g -fsanitize=address,undefined
FLAGS := -Wall -Wextra -Werror

# src and obj files macros
OBJ_PATH := obj
SRC_PATH := src
SRC := $(wildcard $(SRC_PATH)/*.c)
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# VPATH
VPATH := $(SRC_PATH)

# default rule
default: makedir all

# file targets
$(NAME): $(OBJ)
		$(AR) $(NAME) $(OBJ)
		@echo "make: lexer success!"

$(OBJ_PATH)/%.o: %.c
		$(CC) $(FLAGS) $(ADD_FLAGS) -c $< -o $@

# phony targets
all: $(NAME)

makedir:
		@mkdir -p $(OBJ_PATH)

clean:
		@echo "lexer: "
		$(RM) -r $(OBJ_PATH)

fclean: clean
		$(RM) $(NAME)

re: fclean makedir all

.PHONY: all clean fclean re