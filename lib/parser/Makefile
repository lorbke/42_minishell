# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 13:54:25 by lorbke            #+#    #+#              #
#    Updated: 2023/03/11 19:58:15 by fyuzhyk          ###   ########.fr        #
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
NAME   := libparser.a

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

# header macros
LEXER_INC := ../lexer

# VPATH
VPATH     := src

# src and obj files macros
SRC_PATH  := src
OBJ_PATH  := obj
SRC       := parser.c parser_and_or.c parser_free.c\
             parser_pipeline.c parser_simple_command.c\
             parser_subshell.c parser_utils.c
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
	@echo -e -n "$(BLUE)Creating: parser library: $(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo -e "$(GREEN)make: parser success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile parser.h $(SRC_PATH)/private_parser.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(CFLAGS) $(ADD_FLAGS) -I$(LFT_PATH) -I$(LEXER_INC) -I. -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(RED)make: parser cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
