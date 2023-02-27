# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 16:41:09 by lorbke            #+#    #+#              #
#    Updated: 2023/02/27 17:55:16 by fyuzhyk          ###   ########.fr        #
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
CC := gcc
AR := ar rcs
RM := rm -f
CFLAGS := -g #-Wall -Wextra -Werror

# leak sanitizer
LEAKFLAGS := -Wno-gnu-include-next
LEAK_PATH := /Users/lorbke/Coding/TOOLS/LeakSanitizer
LEAK_LINK := -L$(LEAK_PATH) -llsan -lc++
LEAK := $(LEAKFLAGS) $(LEAK_LINK)

# library macros
LIB_PATH := lib
GCOLL_PATH := $(LIB_PATH)/garbage_collector
GCOLL_LIB := garbagecollector
GCOLL_LINK := -L$(GCOLL_PATH) -l$(GCOLL_LIB)
LFT_PATH := $(LIB_PATH)/libft
LFT_LIB := ft
LFT_LINK := -L$(LFT_PATH) -l$(LFT_LIB)
LEXER_PATH := $(LIB_PATH)/lexer
LEXER_LIB := lexer
LEXER_LINK := -L$(LEXER_PATH) -l$(LEXER_LIB)
PARSER_PATH := $(LIB_PATH)/parser
PARSER_LIB := parser
PARSER_LINK := -L$(PARSER_PATH) -l$(PARSER_LIB)
ENV_PATH := $(LIB_PATH)/env
ENV_LIB := env
ENV_LINK := -L$(ENV_PATH) -l$(ENV_LIB)
GNL_PATH = $(LIB_PATH)/gnl
GNL_LIB = gnl
GNL_LINK = -L$(GNL_PATH) -l$(GNL_LIB)
RDLN_LIB := readline
GLBR_PATH := expander/globber

# src and obj files macros
SRC_PATH := src
OBJ_PATH := obj
SRC := $(wildcard $(SRC_PATH)/*.c) $(wildcard $(SRC_PATH)/*/*.c) $(wildcard $(SRC_PATH)/*/*/*.c)
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# VPATH
VPATH := $(SRC_PATH) $(SRC_PATH)/debugger $(SRC_PATH)/executer $(SRC_PATH)/doccer $(SRC_PATH)/builtins $(SRC_PATH)/builtins/cd $(SRC_PATH)/builtins/export $(SRC_PATH)/expander $(SRC_PATH)/utils $(SRC_PATH)/$(GLBR_PATH)

# file targets
$(NAME): $(OBJ_PATH) $(OBJ)
	@$(MAKE) -C $(GCOLL_PATH)
	@$(MAKE) -C $(LFT_PATH)
	@$(MAKE) -C $(LEXER_PATH)
	@$(MAKE) -C $(PARSER_PATH)
	@$(MAKE) -C $(ENV_PATH)
	@$(MAKE) -C $(GNL_PATH)
	@echo -e -n "$(BLUE)Creating: minishell executable: $(RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(GCOLL_LINK) $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) $(EXECUTER_LINK) $(ENV_LINK) $(GNL_LINK) -l$(RDLN_LIB) -o $(NAME)
	@echo -e "$(GREEN)make: minishell success!$(RESET)"
# inc when on macbook
# -L/opt/homebrew/Cellar/readline/8.2.1/lib
# Leak Sanitizer
# -L/Users/fyuzhyk/LeakSanitizer -llsan -lc++

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile $(SRC_PATH)/minishell.h $(SRC_PATH)/debugger.h $(SRC_PATH)/executer.h $(SRC_PATH)/doccer.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(CFLAGS) -I$(GCOLL_PATH) -I$(LFT_PATH) -I$(LEXER_PATH) -I$(PARSER_PATH) -I$(ENV_PATH) -I$(GNL_PATH) -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	@cd $(GCOLL_PATH) && $(MAKE) fclean
	@cd $(LFT_PATH) && $(MAKE) fclean
	@cd $(LEXER_PATH) && $(MAKE) fclean
	@cd $(PARSER_PATH) && $(MAKE) fclean
	@cd $(ENV_PATH) && $(MAKE) fclean
	@cd $(GNL_PATH) && $(MAKE) fclean
	$(RM) $(NAME)
	@echo -e "$(RED)make: minishell cleaned!$(RESET)"

re: fclean all

leak: CFLAGS += $(LEAK)
leak: clean all
	@$(MAKE) clean

test:
	@rm -f tester
	@$(MAKE) -C $(GCOLL_PATH)
	@$(MAKE) -C $(LFT_PATH)
	@$(MAKE) -C $(LEXER_PATH)
	@$(MAKE) -C $(PARSER_PATH)
	@$(MAKE) -C $(ENV_PATH)
	@$(MAKE) -C $(GNL_PATH)
	$(CC) -O0 -DDEBUG -g tester_parser_lexer.c $(SRC_PATH)/debugger/debugger.c -I$(GCOLL_PATH) -I$(SRC_PATH) -I$(LFT_PATH) \
	-I$(LEXER_PATH) -I$(PARSER_PATH) -I$(ENV_PATH) -I$(GNL_PATH) $(GCOLL_LINK) $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) $(ENV_LINK) $(GNL_LINK) -l$(RDLN_LIB) -o tester

.PHONY: all clean fclean re
