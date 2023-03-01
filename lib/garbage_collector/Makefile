# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 13:54:25 by lorbke            #+#    #+#              #
#    Updated: 2023/03/01 16:01:25 by fyuzhyk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SHELL macro
SHELL  := /bin/bash

# colors
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
RESET  := \033[0m

# name macro
NAME   := libgarbagecollector.a

# command macros
CC        := cc
AR        := ar rcs
RM        := rm -f
ADD_FLAGS := #-g -fsanitize=address,undefined
CFLAGS    := -Wall -Wextra -Werror

# VPATH
VPATH     := src

# src and obj files macros
SRC_PATH  := src
OBJ_PATH  := obj
SRC       := garbage_collector.c garbage_collector_free_funcs.c garbage_collector_obj.c
OBJ       := $(SRC:%.c=$(OBJ_PATH)/%.o)

###################################
#	SYSTEM SPECIFIC SETTINGS	  #
###################################

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

###################################
#	RULES						  #
###################################

# file targets
$(NAME): $(OBJ_PATH) $(OBJ)
	@echo -e -n "$(BLUE)Creating: garbage_collector library: $(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo -e "$(GREEN)make: garbage_collector success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile garbage_collector.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(FLAGS) $(ADD_FLAGS) -I. -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(RED)make: garbage_collector cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
