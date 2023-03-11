# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 16:19:43 by fyuzhyk           #+#    #+#              #
#    Updated: 2023/03/11 19:57:35 by fyuzhyk          ###   ########.fr        #
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
NAME   := libenv.a

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
SRC       := env_symtab.c env_symtab_utils.c env_utils.c
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
	@echo -e -n "$(BLUE)Creating: env library: $(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo -e "$(GREEN)make: env success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile env.h $(SRC_PATH)/env_private.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(CFLAGS) $(ADD_FLAGS) -I$(LFT_PATH) -I. -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(RED)make: env cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
