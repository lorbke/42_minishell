# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 13:54:25 by lorbke            #+#    #+#              #
#    Updated: 2023/03/01 16:12:32 by fyuzhyk          ###   ########.fr        #
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
NAME   := liblexer.a

# command macros
CC        := cc
AR        := ar rcs
RM        := rm -f
ADD_FLAGS := #-g -fsanitize=address,undefined
CFLAGS    := -Wall -Wextra -Werror

# library macros
LIB_PATH  := ../
LFT_PATH  := $(LIB_PATH)/libft
LFT_LIB   := ft
LFT_LINK  := -L$(LFT_PATH) -l$(LFT_LIB)

# VPATH
VPATH     := src

# src and obj files macros
SRC_PATH  := src
OBJ_PATH  := obj
SRC       := lexer.c lexer_free.c lexer_utils.c
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
	@$(MAKE) -C $(LFT_PATH)
	@echo -e -n "$(BLUE)Creating: lexer library: $(RESET)"
	$(AR) $(NAME) $(OBJ) $(LFT_PATH)/obj/ft_strdup_size.o
	@echo -e "$(GREEN)make: lexer success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile lexer.h $(SRC_PATH)/private_lexer.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(FLAGS) $(ADD_FLAGS) -I$(LFT_PATH) -I. -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(RED)make: lexer cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
